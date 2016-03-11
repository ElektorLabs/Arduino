/*
  RotaryEncoder.cpp - Rotary encoder driver for Platino.

  Copyright (c) 2011, 2015 Clemens Valens

  12/10/2015 - CPV, Support added for jumpers JP15 and JP16.
  03/02/2012 - CPV, Initials release.
  
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

#include "RotaryEncoder.h"


RotaryEncoder::RotaryEncoder(void)
{
  init();
}


void RotaryEncoder::init(void)
{
  _stateOld = 0;
  _stateSub = 0;
  _value = 0;
  _changed = false;
}


uint8_t RotaryEncoder::tick(uint8_t a, uint8_t b)
{
  uint8_t result = 0;
  uint8_t state = a + (b<<1);
  
  // state is now 0, 1, 2 or 3.
  
  if (state!=_stateOld)
  {
    // Exor the old & new states to determine the rotation direction.
    int8_t inc = ((state>>1)^_stateOld)&0x01;
    if (inc==0) inc = -1;
    _stateOld = state;

    // Reset on change of direction.
    if ((inc<0 && _stateSub>0) || (inc>0 && _stateSub<0)) _stateSub = 0;

    _stateSub += inc;
    if (_stateSub<=-4 || _stateSub>=4)
    {
      _value += inc;
      _stateSub -= (inc<<2);
      _changed = true;
      result = 1;
    }
  }
  
  return result;
}
