/*
  Platino.cpp - drivers for Platino.

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

#include "Arduino.h"


// LCD backlight
#define LCD_BL  ((_jp3=='B')?(13):((_jp3=='C')?(19):(PIN_NOT_SET))) /* PB5 (D7) or PC5 (D19) */

// LCD alternative pinning
#define LCD_RS_MAPPED  ((_jp15=='D')?(LCD_RS):((_jp15=='B')?(LCD_RS_ALT):(PIN_NOT_SET))) /* PD2 (D2) or PB7 (D23) */
#define LCD_E_MAPPED  ((_jp16=='D')?(LCD_E):((_jp16=='B')?(LCD_E_ALT):(PIN_NOT_SET))) /* PD3 (D3) or PB6 (D22) */
// This was for the v1.4 board.
//#define LCD_RS_MAPPED  ((_jp15=='D')?(LCD_RS):((_jp15=='A')?(LCD_RS_ALT):(PIN_NOT_SET))) /* PD2 (D2) or PA6 (D25) */
//#define LCD_E_MAPPED  ((_jp16=='D')?(LCD_E):((_jp16=='A')?(LCD_E_ALT):(PIN_NOT_SET))) /* PD3 (D3) or PA7 (D24) */

// Push buttons
#define S1  ((_jp4=='B')?(8):((_jp4=='C')?(14):(PIN_NOT_SET))) /* PB0 (D8) or PC0 (D14) */
#define S2  ((_jp5=='B')?(9):((_jp5=='C')?(15):(PIN_NOT_SET))) /* PB1 (D9) or PC1 (D15) */
#define S3  ((_jp6=='B')?(10):((_jp6=='C')?(16):(PIN_NOT_SET))) /* PB2 (D10) or PC2 (D16) */
#define S4  ((_jp7=='B')?(11):((_jp7=='C')?(17):(PIN_NOT_SET))) /* PB3 (D11) or PC3 (D17) */

// Buzzer
#define BUZZER  ((_jp4=='B')?(12):((_jp4=='C')?(18):(PIN_NOT_SET))) /* PB4 (D12) or PC4 (D18) */

// RGB LED
#if defined(ATMEGA_X4)
  #define LED_RED_PIN  (20) /* PC6 ** D20 ** ouside ATMEGA_X8 pin range */
  #define LED_GREEN_PIN  ((_jp14=='B')?(13):((_jp14=='C')?(21):(PIN_NOT_SET))) /* PB5 (D13) or PC7 (D21) */
#elif defined(ATMEGA_X8)
  #define LED_RED_PIN  PIN_NOT_SET /* ATMEGA_X8 does not have PC6 */
  #define LED_GREEN_PIN  ((_jp14=='B')?(13):(PIN_NOT_SET)) /* PB5 (D13) or open 'cause ATMEGA_X8 does not have PC7 */
#endif
#define LED_BLUE_PIN  (19) /* PC5 ** D19 */

// Arduino standard LED (on PB5 if jp14 is positionned correctly).
#define LED  LED_GREEN_PIN



CPlatino::CPlatino(void)
{
  init(0,0,0,0,0,0,0,0,0);
}


/*
Solder jumpers
--------------
 JP1: Buzzer,         'B'=PB4, 'C'=PC4, 0=Open
 JP3: LCD backlight,  'B'=PB5, 'C'=PC5, 0=Open
 JP4: S1,             'B'=PB0, 'C'=PC0, 0=Open
 JP5: S2,             'B'=PB1, 'C'=PC1, 0=Open
 JP6: S3,             'B'=PB2, 'C'=PC2, 0=Open
 JP7: S4,             'B'=PB3, 'C'=PC3, 0=Open
JP14: RGB LED 2,      'B'=PB5, 'C'=PC7, 0=Open

New on revision 1.4 (150555-1)
JP15: LCD RS          'B'=PB7, 'D'=PD2', 0=Open
JP16: LCD E(nable)    'B'=PB6, 'D'=PD3', 0=Open

Define JP1, JP3..7 & JP14..16 at the beginning of your sketch
if one or more of these solder jumpers are in place. They
can have a value of 'B' or 'C' or nothing, like this:
JP15 & JP16 can have a value of 'B' or 'D' or nothing, like this:

Platino.begin('B','C','B','B','B','B','B','D','D');

Note that:
 - if JP3=='C' then PC5 is shared between LCD backlight and RGB LED 3.
*/


void CPlatino::showPin(uint8_t pin, uint8_t space)
{
  if (pin==PIN_NOT_SET) pin = 0;
  //if (pin<10) display.print('0');
  display.print(pin);
  if (space) display.print(' ');
}


void CPlatino::init(uint8_t jp1, uint8_t jp3, uint8_t jp4, uint8_t jp5, uint8_t jp6, uint8_t jp7, uint8_t jp14, uint8_t jp15, uint8_t jp16)
{
  _jp1 = toupper(jp1); 
  _jp3 = toupper(jp3); 
  _jp4 = toupper(jp4); 
  _jp5 = toupper(jp5); 
  _jp6 = toupper(jp6); 
  _jp7 = toupper(jp7); 
  _jp14 = toupper(jp14);
  _jp15 = toupper(jp15);
  _jp16 = toupper(jp16);

  _has_display = false;
  _has_backlight = false;
  _has_pushbutton1 = false;
  _has_pushbutton2 = false;
  _has_pushbutton3 = false;
  _has_pushbutton4 = false;
  _has_knob1 = false;
  _has_knob2 = false;
  _has_buzzer = false;
  _has_led_red = false;
  _has_led_green = false;
  _has_led_blue = false;
}


boolean CPlatino::hasDisplay(uint8_t lines, uint8_t columns, boolean true_false, boolean splash)
{ 
  _has_display = false;

  // Setup LCD only if RS and E jumpers are placed correctly.
  if (true_false==true && LCD_RS_MAPPED!=PIN_NOT_SET && LCD_RS_MAPPED!=PIN_NOT_SET)
  {
    display.init(1,LCD_RS_MAPPED,255,LCD_E_MAPPED,LCD_D4,LCD_D5,LCD_D6,LCD_D7,0,0,0,0);
    display.begin(columns,lines);
    display.clear();
    display.noCursor();
    display.setCursor(0,0);
    if (splash==true)
    {
      display.print("Platino");
      display.setCursor(0,1);
      display.print("ATmega");
      display.print(AVR_DEVICE);
      display.print(AVR_DEVICE_VARIANT);
      //showPin(S1);
      //showPin(S2);
      //showPin(S3);
      //showPin(S4);
      //showPin(BUZZER);
      //showPin(LED);
      //showPin(LCD_BL);
      //showPin(LCD_RS_MAPPED);
      //showPin(LCD_E_MAPPED,0);
    }
    _has_display = true;
  }
  return _has_display;
}


boolean CPlatino::hasBacklight(boolean true_false)
{ 
  _has_backlight = false;

  // Setup backlight only if jumpers are placed correctly.
  if (true_false==true && LCD_BL!=PIN_NOT_SET)
  {
    pinMode(LCD_BL,OUTPUT);
    _has_backlight = true;
  }
  return _has_backlight;
}


void CPlatino::backlight(uint8_t value)
{
  if (_has_backlight==true)
  {
    digitalWrite(LCD_BL,value);
  }
}


boolean CPlatino::hasLedColor(uint8_t color, boolean true_false)
{ 
  if (color==LED_RED) // red
  {
    _has_led_red = false;
    // Setup LED only if jumpers are placed correctly.
    if (true_false==true && LED_RED_PIN!=PIN_NOT_SET)
    {
      pinMode(LED_RED_PIN,OUTPUT);
      _has_led_red = true;
    }
    return _has_led_red;
  }
  else if (color==LED_GREEN) // green
  {
    _has_led_green = false;
    // Setup LED only if jumpers are placed correctly.
    if (true_false==true && LED_GREEN_PIN!=PIN_NOT_SET)
    {
      pinMode(LED_GREEN_PIN,OUTPUT);
      _has_led_green = true;
    }
    return _has_led_green;
  }
  else if (color==LED_BLUE) // blue
  {
    _has_led_blue = false;
    // Setup LED only if jumpers are placed correctly.
    if (true_false==true && LED_BLUE_PIN!=PIN_NOT_SET)
    {
      pinMode(LED_BLUE_PIN,OUTPUT);
      _has_led_blue = true;
    }
    return _has_led_blue;
  }
  return false;
}


boolean CPlatino::hasLedRgb(boolean true_false)
{
  uint8_t error = 0;
  if (hasLedColor(LED_RED,true_false)==false) error += 1; // red
  if (hasLedColor(LED_GREEN,true_false)==false) error += 1; // green
  if (hasLedColor(LED_BLUE,true_false)==false) error += 1; // blue
  return error==0;
}


void CPlatino::led(uint8_t color, uint8_t value)
{
  if (color==LED_RED && _has_led_red==true) digitalWrite(LED_RED_PIN,value); // red  
  else if (color==LED_GREEN && _has_led_green==true) digitalWrite(LED_GREEN_PIN,value); // green
  else if (color==LED_BLUE && _has_led_blue==true) digitalWrite(LED_BLUE_PIN,value); // blue 
}


boolean CPlatino::hasBuzzer(boolean true_false)
{ 
  _has_buzzer = false;

  // Setup buzzer only if jumpers are placed correctly.
  if (true_false==true && BUZZER!=PIN_NOT_SET)
  {
    pinMode(BUZZER,OUTPUT);
    _has_buzzer = true;
  }
  return _has_buzzer;
}


void CPlatino::beep(unsigned int frequency, unsigned long duration)
{
  if (_has_buzzer==true)
  {
    tone(BUZZER,frequency,duration);
  }
}


boolean CPlatino::hasPushbutton(uint8_t nr, boolean true_false)
{ 
  if (nr==1)
  {
    _has_pushbutton1 = false;
    // Setup pushbutton only if jumpers are valid.  
    if (true_false==true && S1!=PIN_NOT_SET)
    {
      pushbutton1.init(S1);
      _has_pushbutton1 = true;
    }
    return _has_pushbutton1;
  }
  else if (nr==2)
  {
    _has_pushbutton2 = false;
    // Setup pushbutton only if jumpers are valid.  
    if (true_false==true && S2!=PIN_NOT_SET)
    {
      pushbutton2.init(S2);
      _has_pushbutton2 = true;
    }
    return _has_pushbutton2;
  }
  else if (nr==3)
  {
    _has_pushbutton3 = false;
    // Setup pushbutton only if jumpers are valid.  
    if (true_false==true && S3!=PIN_NOT_SET)
    {
      pushbutton3.init(S3);
      _has_pushbutton3 = true;
    }
    return _has_pushbutton3;
  }
  else if (nr==4)
  {
    _has_pushbutton4 = false;
    // Setup pushbutton only if jumpers are valid.  
    if (true_false==true && S4!=PIN_NOT_SET)
    {
      pushbutton4.init(S4);
      _has_pushbutton4 = true;
    }
    return _has_pushbutton4;
  }
  return false;
}


uint8_t CPlatino::pushbuttonRead(uint8_t nr, boolean clear)
{
       if (nr==1 && _has_pushbutton1==true) return pushbutton1.read(clear);
  else if (nr==2 && _has_pushbutton2==true) return pushbutton2.read(clear);
  else if (nr==3 && _has_pushbutton3==true) return pushbutton3.read(clear);
  else if (nr==4 && _has_pushbutton4==true) return pushbutton4.read(clear);
  return PUSHBUTTON_IDLE;
}


void CPlatino::pushbuttonClear(uint8_t nr)
{
       if (nr==1 && _has_pushbutton1==true) pushbutton1.clear();
  else if (nr==2 && _has_pushbutton2==true) pushbutton2.clear();
  else if (nr==3 && _has_pushbutton3==true) pushbutton3.clear();
  else if (nr==4 && _has_pushbutton4==true) pushbutton4.clear();
}


boolean CPlatino::hasKnob(uint8_t nr, boolean true_false)
{ 
  if (nr==1)
  {
    _has_knob1 = false;
    // Setup rotary encoder only if jumpers are valid.  
    if (true_false==true && S1!=PIN_NOT_SET && S2!=PIN_NOT_SET)
    {
      // Make sure corresponding pushbuttons are initialised.
      if (_has_pushbutton1==false) hasPushbutton(1,true);
      if (_has_pushbutton2==false) hasPushbutton(2,true);
      knob1.init();
      _has_knob1 = _has_pushbutton1 && _has_pushbutton2;
      return _has_knob1;
    }
  }
  else if (nr==2)
  {
    _has_knob2 = false;
    // Setup rotary encoder only if jumpers are valid.  
    if (true_false==true && S3!=PIN_NOT_SET && S4!=PIN_NOT_SET)
    {
      // Make sure corresponding pushbuttons are initialised.
      if (_has_pushbutton3==false) hasPushbutton(3,true);
      if (_has_pushbutton4==false) hasPushbutton(4,true);
      knob2.init();
      _has_knob2 = _has_pushbutton3 && _has_pushbutton4;
      return _has_knob2;
    }
  }
  return false;
}


boolean CPlatino::knobChanged(uint8_t nr)
{
  if (nr==1 && _has_knob1==true) return knob1.changed();
  else if (nr==2 && _has_knob2==true) return knob2.changed();
  return false;
}


int16_t CPlatino::knobRead(uint8_t nr)
{
  if (nr==1 && _has_knob1==true) return knob1.read();
  else if (nr==2 && _has_knob2==true) return knob2.read();
  return 0;
}


void CPlatino::knobWrite(uint8_t nr, int16_t value)
{
  if (nr==1 && _has_knob1==true) knob1.write(value);
  else if (nr==2 && _has_knob2==true) knob2.write(value);
}


void CPlatino::tick(void)
{
  if (_has_pushbutton1==true)
  {
    pushbutton1.debounce();
  }
  if (_has_pushbutton2==true)
  {
    pushbutton2.debounce();
  }
  if (_has_pushbutton3==true)
  {
    pushbutton3.debounce();
  }
  if (_has_pushbutton4==true)
  {
    pushbutton4.debounce();
  }

  if (_has_knob1==true)
  {
    uint8_t a = pushbutton1.read(false);
    uint8_t b = pushbutton2.read(false);
    if (a!=PUSHBUTTON_IDLE && b!=PUSHBUTTON_IDLE)
    {
      knob1.tick(a,b);
    }
  }
  
  if (_has_knob2==true)
  {
    uint8_t a = pushbutton3.read(false);
    uint8_t b = pushbutton4.read(false);
    if (a!=PUSHBUTTON_IDLE && b!=PUSHBUTTON_IDLE)
    {
      knob2.tick(a,b);
    }
  }
}


// The global Platino object.
CPlatino Platino;


// This hack is needed to make tick callable from the timer0 ISR (in wiring.c).
#ifdef __cplusplus
extern "C"{
#endif
void platino_tick(void)
{
  Platino.tick();
}
#ifdef __cplusplus
} // extern "C"
#endif
