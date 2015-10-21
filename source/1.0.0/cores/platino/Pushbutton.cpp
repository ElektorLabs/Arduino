/*
  Pushbutton.cpp - Pushbutton driver for Platino.

  Copyright (c) 2011, 2015 Clemens Valens

  12/10/2015 - CPV, Support added for jumpers JP15 and JP16.
  03/02/2012 - CPV, Initial release.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

*/

#include "Arduino.h"
#include "Pushbutton.h"



Pushbutton::Pushbutton(void)
{
  init(PIN_NOT_SET);
}


Pushbutton::Pushbutton(uint8_t pin)
{
  init(pin);
}


void Pushbutton::init(uint8_t pin, int8_t debounceMin, int8_t debounceMax)
{
  _debounce = 0;
  _state = PUSHBUTTON_IDLE;
  _pin = pin;
  if (_pin!=PIN_NOT_SET) pinMode(_pin,INPUT);
  _debounceMin = debounceMin;
  _debounceMax = debounceMax;
}


uint8_t Pushbutton::debounce(void)
{
  uint8_t debounced = 0;
  
  if (digitalRead(_pin)!=0)
  {
    // Button released.
    if (_debounce<_debounceMax)
    {
      _debounce += 1;
    }
    else if (_debounce==_debounceMax)
    {
      _debounce += 1;
      _state = PUSHBUTTON_UP;
      debounced = 1; 
    }
    else debounced = 1; 
  }
  else
  {
    // Button pressed (active low).
    if (_debounce>_debounceMin)
    {
      _debounce -= 1;
    }
    else if (_debounce==_debounceMin)
    {
      _debounce -= 1;
      _state = PUSHBUTTON_DOWN;
      debounced = 1; 
    }
    else debounced = 1; 
  }
  
  return debounced;
}


uint8_t Pushbutton::read(boolean clear)
{
  uint8_t temp = _state;
  if (clear==true) _state = PUSHBUTTON_IDLE;
  return temp;
}


uint8_t Pushbutton::readDebounced(void)
{
  if (_pin!=PIN_NOT_SET)
  {
    while (debounce()==0);
    return read();
  }
  return (uint8_t)-1;
}
