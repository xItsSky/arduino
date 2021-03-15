/*#include "CapteurMouvement.h"

CapteurMouvement::CapteurMouvement() {
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);
  CurieIMU.setDetectionThreshold(CURIE_IMU_MOTION, 20); // 20mg
  CurieIMU.setDetectionDuration(CURIE_IMU_MOTION, 10);  // trigger times of consecutive slope data points
  CurieIMU.interrupts(CURIE_IMU_MOTION);
  
  countUntilShake = 0;
  interruptsTime = 0;  
}

int CapteurMouvement::getCountUntilShake() {
  return countUntilShake;
}

void CapteurMouvement::setCountUntilShake(int val) {
  countUntilShake = val;
}

static void CapteurMouvement::eventCallback(void){
  if (CurieIMU.getInterruptStatus(CURIE_IMU_MOTION)) {
    if (CurieIMU.motionDetected(Y_AXIS, POSITIVE))
      countUntilShake++;
    if (CurieIMU.motionDetected(Y_AXIS, NEGATIVE))
      countUntilShake++;
    interruptsTime = millis(); 
  }
}*/
