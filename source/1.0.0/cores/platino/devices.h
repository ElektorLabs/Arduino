/*
  package.h - Chip package definitions.

  Copyright (c) 2011, 2015 Clemens Valens

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

#ifndef __DEVICES_H__
#define __DEVICES_H__


// AVRdude may not know of all these devices. 
// Add them to the avrdude.conf file by copying
// an existing device of the same type in this file, 
// rename it and change the device signature.

//
// 40-pin devices.
//
#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || \
  defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__) || \
  defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__) || \
  defined(__AVR_ATmega324__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || \
  defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) || \
  defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#define ATMEGA_X4

//
// 28-pin devices
//
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega8A__) || \
  defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || \
  defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || \
  defined(__AVR_ATmega168__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168PA__) || \
  defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define ATMEGA_X8
#endif


#if defined(__AVR_ATmega1284__)
  #define AVR_DEVICE  (1284)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega1284P__)
  #define AVR_DEVICE  (1284)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega644__)
  #define AVR_DEVICE  (644)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega644A__)
  #define AVR_DEVICE  (644)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega644P__)
  #define AVR_DEVICE  (644)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega644PA__)
  #define AVR_DEVICE  (644)
  #define AVR_DEVICE_VARIANT  ("PA")
#elif defined(__AVR_ATmega328__)
  #define AVR_DEVICE  (328)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega328P__)
  #define AVR_DEVICE  (328)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega324A__)
  #define AVR_DEVICE  (324)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega324P__)
  #define AVR_DEVICE  (324)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega324PA__)
  #define AVR_DEVICE  (324)
  #define AVR_DEVICE_VARIANT  ("PA")
#elif defined(__AVR_ATmega168__)
  #define AVR_DEVICE  (168)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega168A__)
  #define AVR_DEVICE  (168)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega168P__)
  #define AVR_DEVICE  (168)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega168PA__)
  #define AVR_DEVICE  (168)
  #define AVR_DEVICE_VARIANT  ("PA")
#elif defined(__AVR_ATmega164A__)
  #define AVR_DEVICE  (164)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega164P__)
  #define AVR_DEVICE  (164)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega164PA__)
  #define AVR_DEVICE  (164)
  #define AVR_DEVICE_VARIANT  ("PA")
#elif defined(__AVR_ATmega88__)
  #define AVR_DEVICE  (88)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega88A__)
  #define AVR_DEVICE  (88)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega88P__)
  #define AVR_DEVICE  (88)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega88PA__)
  #define AVR_DEVICE  (88)
  #define AVR_DEVICE_VARIANT  ("PA")
#elif defined(__AVR_ATmega48__)
  #define AVR_DEVICE  (48)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega48A__)
  #define AVR_DEVICE  (48)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega48P__)
  #define AVR_DEVICE  (48)
  #define AVR_DEVICE_VARIANT  ("P")
#elif defined(__AVR_ATmega48PA__)
  #define AVR_DEVICE  (48)
  #define AVR_DEVICE_VARIANT  ("PA")
#elif defined(__AVR_ATmega32__)
  #define AVR_DEVICE  (32)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega32A__)
  #define AVR_DEVICE  (32)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega16__)
  #define AVR_DEVICE  (16)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega16A__)
  #define AVR_DEVICE  (16)
  #define AVR_DEVICE_VARIANT  ("A")
#elif defined(__AVR_ATmega8__)
  #define AVR_DEVICE  (8)
  #define AVR_DEVICE_VARIANT  ("")
#elif defined(__AVR_ATmega8A__)
  #define AVR_DEVICE  (8)
  #define AVR_DEVICE_VARIANT  ("A")
#endif


#endif /* __DEVICES_H__ */
