/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef gesture_h
#define gesture_h
#include "Arduino.h"
#include "paj7620.h"

class Gesture
{
  public:
    Gesture();
    int returnGeste();
    void test();
  private:
    // Utilisé pour le capteur de geste
    int GES_REACTION_TIME  =  500;     // You can adjust the reaction time according to the actual circumstance.
    int GES_ENTRY_TIME     = 800;    // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
    int GES_QUIT_TIME    = 1000;
    uint8_t _error = 0;
};

#endif
