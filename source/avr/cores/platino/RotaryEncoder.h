/*
  RotaryEncoder.h - Rotary encoder driver for Platino.

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

#ifndef __ROTARY_ENCODER_H__
#define __ROTARY_ENCODER_H__


#include <inttypes.h>


/*
 * The optional push-button of a rotary encoder is not included
 * in this class and should be handled as a normal push-button.
 */

class RotaryEncoder
{
  private:
    uint8_t _stateOld;
    int8_t _stateSub;
    int16_t _value;
    int8_t _changed;

  public:
    RotaryEncoder(void);
    void init(void);

    uint8_t changed(void) { return _changed; }
    int16_t read(void) { _changed = false; return _value; }
    void write(int16_t value) { /*cli();*/ _value = value; _changed = true; /*sei();*/ }
    
    // Call this function regularly, like every millisecond or so.
    uint8_t tick(uint8_t a, uint8_t b);
};


#endif /* __ROTARY_ENCODER_H__ */
