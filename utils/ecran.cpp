

/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ecran.h"

Ecran::Ecran()
{
	_lcd.begin(16, 2);
}
void Ecran::affichage(char* line1 ,char* line2 )
{
   _lcd.setCursor(0, 0);
   _lcd.print(line1);
   _lcd.setCursor(0, 1);
   _lcd.print(line2);
}
