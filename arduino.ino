/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/

// Utilisé pour le bluetooth
#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
#include <ChainableLED.h>
#include <ArduinoSTL.h>
using namespace std;

// Utilisé pour le capteur de geste
#include <Wire.h>
#include "paj7620.h"

// Utilisé pour le capteur de mouvement
#include "CurieIMU.h"

// INCLUDE DES UTILS
#include "utils/BuzzerNotes.h"
#include "utils/touch.cpp"

// INCLUDE DU MODELE
#include "modele/Group.cpp"
#include "modele/User.cpp"
#include "modele/Task.cpp"
#include "modele/GroupFactory.cpp"
#include "modele/UserFactory.cpp"
#include "modele/TaskFactory.cpp"

/*******************************************************************************
 *                              DEFINES                                        *
 *******************************************************************************/

// Utilisé pour le bluetooth
#define BLYNK_PRINT Serial

// Utilisé pour le capteur de geste
#define GES_REACTION_TIME    500
#define GES_ENTRY_TIME      800
#define GES_QUIT_TIME     1000

/*******************************************************************************
 *                              VARIABLES                                      *
 *******************************************************************************/

// Factories
GroupFactory* groups = GroupFactory::getInstance();
UserFactory* users = UserFactory::getInstance();
TaskFactory* tasks = TaskFactory::getInstance();

// Variables de gestions
int currentDisplayedGroup = 0;

// Les pins
const int pin = 4;
const int pin_data = 5;
int pinBuzzer = 3;
const int pinTouch = 2;

// Utilisé pour le capteur tactile
touch touch(pinTouch);
int saveTap = 0;

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

Group* group1;
Group* group2;

/*******************************************************************************
 *                              BLUETOOTH                                      *
 *******************************************************************************/

// Les pins virtuelles utilisés pour le bluetooth
// Quand on fait une action, c'est ici qu'on récupère les valeurs avec param.astInt
BLYNK_WRITE(V1) // Changement de couleur du groupe 1
{
  // Récupère les couleurs RGB
  int redValue = param[0].asInt();
  int greenValue = param[1].asInt();
  int blueValue = param[2].asInt();

  // Transforme en HEXA
  long rgb = ((long)redValue << 16L) | ((long)greenValue << 8L) | (long)blueValue;
  String hexa = "#" + String(rgb, HEX);
  char c[255];
  hexa.toCharArray(c, 255);

  // Set la couleur au groupe 1
  group1->setColor(c);
  
  //leds.setColorRGB(0, redValue, greenValue, blueValue);
}
BLYNK_WRITE(V2) // Changement de couleur du groupe 2
{
  // Récupère les couleurs RGB
  int redValue = param[0].asInt();
  int greenValue = param[1].asInt();
  int blueValue = param[2].asInt();

  // Transforme en HEXA
  long rgb = ((long)redValue << 16L) | ((long)greenValue << 8L) | (long)blueValue;
  String hexa = "#" + String(rgb, HEX);
  char c[255];
  hexa.toCharArray(c, 255);

  // Set la couleur au groupe 2
  group2->setColor(c);

  //leds.setColorRGB(0, redValue, greenValue, blueValue);
}
BLYNK_WRITE(V3) // Changement de son du groupe 1
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

BLYNK_WRITE(V4) // Changement de son du groupe 2
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

/*******************************************************************************
 *                                  SETUP                                      *
 *******************************************************************************/
 
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

  // initialise the groups, users and tasks factories
  initFactories();

  //task->nextState(); // Pour changer d'état
}

/*******************************************************************************
 *                                  LOOP                                       *
 *******************************************************************************/
 
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

  // Utilisé pour le capteur tactile
  if (touch.detection() != saveTap) {
    if (touch.detection() == 0) {
      
      Serial.print("touch : ");
      Serial.println(saveTap);
      saveTap = touch.detection();
    } else if (touch.detection() == 1) {
      saveTap = touch.detection();
    } else if (touch.detection() == 2) {
      saveTap = touch.detection();
    } else if (touch.detection() == 3) {
      saveTap = touch.detection();
    }
  }
}

/**
 * Initialise the groups, users and tasks factories
 */
void initFactories() {
  // tasks
  Task* task1 = new Task(1, (char*)"Réaliser les classes métiers");
  Task* task2 = new Task(2, (char*)"Tester les classes métiers");
  Task* task3 = new Task(3, (char*)"Réaliser le code Arduino");
  Task* task4 = new Task(4, (char*)"Tester le code Arduino");

  tasks->create(task1);
  tasks->create(task2);
  tasks->create(task3);
  tasks->create(task4);

  // users
  User* user1 = new User(1, (char*)"Quentin");
  user1->addTask(task1);
  User* user2 = new User(2, (char*)"Romain");
  user2->addTask(task3);
  User* user3 = new User(3, (char*)"Valentin");
  user3->addTask(task2);
  user3->addTask(task4);

  users->create(user1);
  users->create(user2);
  users->create(user3);

  // groups
  group1 = new Group(1, (char*)"Groupe 1", (char*)"#FF0000", 1);
  group1->addUser(user1);
  group1->addUser(user2);
  group2 = new Group(2, (char*)"Groupe 2", (char*)"#0000FF", 2);
  group2->addUser(user3);

  groups->create(group1);
  groups->create(group2);
}

/***
 * Switch the displayed group to the next group
 */
void nextGroup() {
  int nbGroup = (int)groups->findAll().size();
  currentDisplayedGroup = (currentDisplayedGroup + 1) % nbGroup;
}

/**
 * Switch the displayed group to the previous group
 */
void previousGroup() {
  int nbGroup = (int)groups->findAll().size();
  currentDisplayedGroup = (currentDisplayedGroup - 1 > 0 ? currentDisplayedGroup - 1 : 2) % nbGroup;
}

/**
 * Return the displayed group
 */
Group* getDisplayedGroup() {
  return groups->find(currentDisplayedGroup);
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
