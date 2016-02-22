/*
  Platino.cpp - drivers for Platino.

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

#ifndef __PLATINO_H__
#define __PLATINO_H__


/*
Definitions for Platino.

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


#include "LiquidCrystal.h"
#include "RotaryEncoder.h"
#include "Pushbutton.h"


// LCD
#define LCD_RS  (2) /* PD2 ** D2 */
//#define LCD_RS_ALT  (23) /* PB7 ** D23 */
#define LCD_RS_ALT  (25) /* PA6 ** D25 */
#define LCD_E  (3) /* PD3 ** D3 */
//#define LCD_E_ALT  (22) /* PB6 ** D22 */
#define LCD_E_ALT  (24) /* PA7 ** D24 */
#define LCD_D4  (4) /* PD4 ** D4 */
#define LCD_D5  (5) /* PD5 ** D5 */
#define LCD_D6  (6) /* PD6 ** D6 */
#define LCD_D7  (7) /* PD7 ** D7 */


#define LED_RED  (1)
#define LED_GREEN  (2)
#define LED_BLUE  (3)


class CPlatino
{
  private:
    uint8_t _jp1;
    uint8_t _jp3;
    uint8_t _jp4;
    uint8_t _jp5;
    uint8_t _jp6;
    uint8_t _jp7;
    uint8_t _jp14;
    uint8_t _jp15;
    uint8_t _jp16;
    boolean _has_display;
    boolean _has_backlight;
    boolean _has_knob1;
    boolean _has_knob2;
    boolean _has_pushbutton1;
    boolean _has_pushbutton2;
    boolean _has_pushbutton3;
    boolean _has_pushbutton4;
    boolean _has_buzzer;
    boolean _has_led_red;
    boolean _has_led_green;
    boolean _has_led_blue;

    Pushbutton pushbutton1;
    Pushbutton pushbutton2;
    Pushbutton pushbutton3;
    Pushbutton pushbutton4;
    RotaryEncoder knob1;
    RotaryEncoder knob2;
    
    void showPin(uint8_t pin, uint8_t space=1);

  public:
    CPlatino();
    
    void init(uint8_t jp1, uint8_t jp3, uint8_t jp4, uint8_t jp5, uint8_t jp6, uint8_t jp7, uint8_t jp14, uint8_t jp15, uint8_t jp16);

    // Step 1. Call begin, f. ex.: Platino.begin(); // Use default jumper settings.
    void begin(uint8_t jp1='B', uint8_t jp3='C', uint8_t jp4='B', uint8_t jp5='B', uint8_t jp6='B', uint8_t jp7='B', uint8_t jp14='B', uint8_t jp15='D', uint8_t jp16='D')
    {
      init(jp1,jp3,jp4,jp5,jp6,jp7,jp14,jp15,jp16);
    }

    // Step 2. Call one or more hasXXX functions to activate the peripherals that are mounted on the board.
    boolean hasDisplay(uint8_t lines=2, uint8_t columns=16, boolean true_false=true, boolean splash=false);
    boolean hasBacklight(boolean true_false=true);
    boolean hasLedColor(uint8_t color=LED_GREEN, boolean true_false=true);
    boolean hasLed(boolean true_false=true) { return hasLedColor(LED_GREEN,true_false); }
    boolean hasLedRgb(boolean true_false=true);
    boolean hasBuzzer(boolean true_false=true);
    boolean hasPushbutton(uint8_t nr, boolean true_false=true);
    boolean hasKnob(uint8_t nr, boolean true_false=true);

    // Step 3. Use the peripherals.
    uint8_t pushbuttonRead(uint8_t nr, boolean clear=true);
    void pushbuttonClear(uint8_t nr);
    // Rotary encoders.
    boolean knobChanged(uint8_t nr);
    int16_t knobRead(uint8_t nr);
    void knobWrite(uint8_t nr, int16_t value);
    // LCD.
    LiquidCrystal display;
    void backlight(uint8_t value);
    // LEDs
    void led(uint8_t color, uint8_t value);
    void led(uint8_t value) { led(LED_GREEN,value); }
    void ledRgb(uint8_t red, uint8_t green, uint8_t blue) { led(LED_RED,red); led(LED_GREEN,green); led(LED_BLUE,blue); }
    // Buzzer
    void beep(unsigned int frequency, unsigned long duration);
    
    // This is called from the Timer0 ISR.
    void tick(void);
};


extern CPlatino Platino;


#endif /* __PLATINO_H__ */
