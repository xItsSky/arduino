
/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "touch.h"

touch::touch(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  myTime = millis();
}
int touch::detection(){
  int val = digitalRead(_pin);
  if(val == 1 && val != previous){
    myTime = millis();
    if(nbTap >= 1){
      if((millis() - myTime) < 500){
        nbTap++;
      }
    }else{
      nbTap = 1;
      high=!high;
    }
  }

  if(!high){ 
    nbTap = 0;
  }else

  switch(nbTap){
    case 1:  
      if((millis() - myTime) > 500){
        nbTap = 0;
      }
      
      break;
    case 2:  
      if((millis() - myTime) > 500){
        nbTap = 0;
      }
      break;
    case 3:  
      if((millis() - myTime) > 500){
        nbTap = 0;
      }
      break;
    default:
      nbTap = 0;
  }
  previous = val;
  return nbTap;
}
int touch::getNbTap(){
  return nbTap;
}
