/*
  Pushbutton.h - Pushbutton driver for Platino.

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

#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__


#include <inttypes.h>


#define DEBOUNCE_MIN_VALUE  (0)
#define DEBOUNCE_MAX_VALUE  (2)
#define PIN_NOT_SET  (255)
#define PUSHBUTTON_DOWN  (0)
#define PUSHBUTTON_UP  (1)
#define PUSHBUTTON_IDLE  (2)


class Pushbutton
{
  private:
    uint8_t _pin;
    int8_t _debounce;
    int8_t _debounceMin;
    int8_t _debounceMax;
    uint8_t _state;

  public:
    Pushbutton(void);
    Pushbutton(uint8_t pin);
    void init(uint8_t pin, int8_t debounceMin=DEBOUNCE_MIN_VALUE, int8_t debounceMax=DEBOUNCE_MAX_VALUE);
    uint8_t debounce(void);
    uint8_t read(boolean clear=true);
    void clear(void) { _state = PUSHBUTTON_IDLE; }
    uint8_t readDebounced(void);
};


#endif /* __PUSHBUTTON_H__ */

