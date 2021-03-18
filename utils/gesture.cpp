
/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "gesture.h"

// Utilisé pour le capteur de geste
#include "paj7620.h"

Gesture::Gesture()
{
  _error = paj7620Init();
}

int Gesture::returnGeste(){
  uint8_t data = 0, _error;
  _error = paj7620ReadReg(0x43, 1, &data);
  if (!_error)
  {
    switch (data) {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        return 1;
        break;
      case GES_LEFT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        return 2;
        break;
      default:
        break;
    }
  }
  return 0;
}
