#include <ArduinoSTL.h>

// Utilisé pour le bluetooth
#define BLYNK_PRINT Serial
#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
#include <ChainableLED.h>

using namespace std;

// Utilisé pour le capteur de geste
#include <Wire.h>
#include "paj7620.h"

// Utilisé pour le capteur de mouvement
#include "CurieIMU.h"

// INCLUDE DES UTILS
#include "utils/BuzzerNotes.h"

// INCLUDE DU MODELE
#include "modele/Group.cpp"
#include "modele/User.cpp"
#include "modele/Task.cpp"

// Utilisé pour le capteur de geste
#define GES_REACTION_TIME    500       // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME      800       // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME     1000

// Les pins
const int pin = 4;
const int pin_data = 5;
int pinBuzzer = 3;

// C,D,E,F,G,A,B avec C = DO
// Variables pour le son
const int maxNotes = 9;
int endTaskSound1[][maxNotes] = {
  {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, 0}, // Notes à jouer (définies dans BuzzerNotes.h)
  {4, 12, 12, 4, 4, 4, 4, 4, 0} // Durée de la note
};
int endTaskSound2[][maxNotes] = {
  {NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, 0, NOTE_D4, 0, 0}, // Notes à jouer (définies dans BuzzerNotes.h)
  {4, 4, 4, 4, 4, 4, 4, 0, 0} // Durée de la note
};
int endTaskSound[2][maxNotes] = {};

// Led pour la couleur de groupe
ChainableLED leds(pin, pin_data, 1);

// Variable pour le bluetooth
char auth[] = "_fMOO1biadye2sn2M4Qn6g2pXLa1ULj8";
BLEPeripheral  blePeripheral;

// Variable pour le capteur de mouvement
int countUntilShake = 0;
unsigned long interruptsTime = 0;    // get the time when motion event is detected

// Les pins virtuelles utilisés pour le bluetooth*
// Quand on fait une action, c'est ici qu'on récupère les valeurs avec param.astInt
BLYNK_WRITE(V1)
{
  int redValue = param[0].asInt();
  int greenValue = param[1].asInt();
  int blueValue = param[2].asInt();

  leds.setColorRGB(0, redValue, greenValue, blueValue);
}
BLYNK_WRITE(V2)
{
  int redValue = param[0].asInt();
  int greenValue = param[1].asInt();
  int blueValue = param[2].asInt();

  leds.setColorRGB(0, redValue, greenValue, blueValue);
}
BLYNK_WRITE(V3)
{
  int soundValue = param.asInt();

  if (soundValue == 1)
    memcpy(endTaskSound, endTaskSound1, sizeof(endTaskSound));
  else
    memcpy(endTaskSound, endTaskSound2, sizeof(endTaskSound));

  for (int thisNote = 0; thisNote < maxNotes; thisNote++) {
    int noteDuration = 1000 / endTaskSound[1][thisNote];
    tone(3, endTaskSound[0][thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(3);
  }
}

BLYNK_WRITE(V4)
{
  int soundValue = param.asInt();

  if (soundValue == 1)
    memcpy(endTaskSound, endTaskSound1, sizeof(endTaskSound));
  else
    memcpy(endTaskSound, endTaskSound2, sizeof(endTaskSound));

  for (int thisNote = 0; thisNote < maxNotes; thisNote++) {
    int noteDuration = 1000 / endTaskSound[1][thisNote];
    tone(3, endTaskSound[0][thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(3);
  }
}


///////////////////////////////////////////////
////////////////// SETUP //////////////////////
///////////////////////////////////////////////
void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(1000);

  // Utilisé pour le bluetooth
  blePeripheral.setLocalName("Blynk");
  blePeripheral.setDeviceName("Blynk");
  blePeripheral.setAppearance(384);
  Blynk.begin(blePeripheral, auth);
  blePeripheral.begin();

  leds.init();

  // Utilisé pour le capteur de geste
  uint8_t error = 0;
  error = paj7620Init();

  // Utilisé pour le capteur de mouvement
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);
  CurieIMU.setDetectionThreshold(CURIE_IMU_MOTION, 20); // 20mg
  CurieIMU.setDetectionDuration(CURIE_IMU_MOTION, 10);  // trigger times of consecutive slope data points
  CurieIMU.interrupts(CURIE_IMU_MOTION);

  Group* group = new Group(1);
  User* user = new User("Quentin");
  Task* task = new Task("mytask");

  group->setName("Groupe de test");
  group->setColor("#FF0000");

  vector<User*> vec;
  vec.push_back(user);
  vec.push_back(user);
  vec.push_back(user);

  group->getUser()->push_back(user);
  group->getUser()->push_back(user);
  group->getUser()->push_back(user);

  task->nextState();
  user->addTask(task);
}

///////////////////////////////////////////////
/////////////////// LOOP //////////////////////
///////////////////////////////////////////////
void loop()
{
  // Utilisé pour le bluetooth
  blePeripheral.poll();
  Blynk.run();

  // Utilisée pour le capteur de geste
  uint8_t data = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);
  if (!error)
  {
    switch (data) {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
        }
        break;
      case GES_LEFT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Left");
        }
        break;
      default:
        break;
    }
  }

  // Utilisée pour le capteur de mouvement
  if (countUntilShake >= 4) {
    countUntilShake = 0;
    Serial.println("Secousse");
  }

  delay(100);
}


// Utilisée pour le capteur de mouvement
static void eventCallback(void) {
  if (CurieIMU.getInterruptStatus(CURIE_IMU_MOTION)) {
    if (CurieIMU.motionDetected(Y_AXIS, POSITIVE))
      countUntilShake++;
    if (CurieIMU.motionDetected(Y_AXIS, NEGATIVE))
      countUntilShake++;
    interruptsTime = millis();
  }
}
