/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ecran_h
#define ecran_h

#include "Arduino.h"
#include "rgb_lcd.h"

class Ecran
{
  public:
	  Ecran();
    void affichage(char* line1 , char* line2);
  private:
    rgb_lcd _lcd;
};

#endif
