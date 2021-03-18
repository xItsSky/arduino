/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef touch_h
#define touch_h

#include "Arduino.h"

class touch
{
  public:
    touch(int pin);
    int detection();
    int getNbTap();
    int nbDetection();
  private:
    int _pin;
    int nbTap = 0;
    int previous;
    int myTime;
    bool high = false;
};

#endif
