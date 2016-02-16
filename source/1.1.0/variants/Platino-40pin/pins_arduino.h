/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

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

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 24 : -1)

#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
#define digitalPinHasPWM(p)         ((p) == 4 || (p) == 5 || (p) == 7 || (p) == 11)
#else
#define digitalPinHasPWM(p)         ((p) == 4 || (p) == 5 || (p) == 6 || (p) == 7 || (p) == 11 || (p) == 12)
#endif

const static uint8_t SS   = 12;
const static uint8_t MOSI = 13;
const static uint8_t MISO = 22;
const static uint8_t SCK  = 23;

const static uint8_t SDA = 15;
const static uint8_t SCL = 14;
#define LED_BUILTIN = 13;

const static uint8_t A0 = 31;
const static uint8_t A1 = 30;
const static uint8_t A2 = 29;
const static uint8_t A3 = 28;
const static uint8_t A4 = 27;
const static uint8_t A5 = 26;
const static uint8_t A6 = 25;
const static uint8_t A7 = 24;

/*
These macros are used by at least the SoftwareSerial library.
*/
#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)
#define digitalPinToPCICR(p)    ((uint8_t *)0)
#define digitalPinToPCICRbit(p) 0
#define digitalPinToPCMSK(p)    ((uint8_t *)0)
#define digitalPinToPCMSKbit(p) 0
#else
#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 31) ? (&PCICR) : ((uint8_t *)0))
// Note: Port B is numbered D8..13,22,23
#define digitalPinToPCICRbit(p) (((p)<=7)? 3 : (((p)<=13)? 1 : (((p)<=21)? 2 : (((p)<=23)? 1 : 0 ))))
// Note: Port B is numbered D8..13,22,23
#define digitalPinToPCMSK(p)    (((p)<=7)? (&PCMSK3) : (((p)<=13)? (&PCMSK1) : (((p)<=21)? (&PCMSK2) : (((p)<=23)? (&PCMSK1) : (((p)<=31)? (&PCMSK0):((uint8_t *)0))))))
// Note: Port A is numbered in reverse, i.e. D24..31 = PA7..0 = PCINT7..0
#define digitalPinToPCMSKbit(p) (((p)<=7)? (p) : (((p)<=13)? ((p)-8) : (((p)<=21)? ((p)-14) : (((p)<=23)? ((p)-8) : (31-(p))))))
#endif

#ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// Atmel ATmegaXX4 / Platino DIP40
//
//                     +---\/---+
//          (D8) PB0  1|        |40  PA0 (AI0 / D31)
//          (D9) PB1  2|        |39  PA1 (AI1 / D30)
//         (D10) PB2  3|        |38  PA2 (AI2 / D29)
//     PWM (D11) PB3  4|        |37  PA3 (AI3 / D28)
// PWM*/SS (D12) PB4  5|        |36  PA4 (AI4 / D27)
//    MOSI (D13) PB5  6|        |35  PA5 (AI5 / D26)
//    MISO (D22) PB6  7|        |34  PA6 (AI6 / D25)
//     SCK (D23) PB7  8|        |33  PA7 (AI7 / D24)
//               RST  9|        |32  AREF
//               VCC 10|        |31  GND 
//               GND 11|        |30  AVCC
//             XTAL2 12|        |29  PC7 (D21)
//             XTAL1 13|        |28  PC6 (D20)
//      RX0 (D0) PD0 14|        |27  PC5 (D19) 
//      TX0 (D1) PD1 15|        |26  PC4 (D18) 
//      RX1 (D2) PD2 16|        |25  PC3 (D17) 
//      TX1 (D3) PD3 17|        |24  PC2 (D16) 
//      PWM (D4) PD4 18|        |23  PC1 (D15) SDA
//      PWM (D5) PD5 19|        |22  PC0 (D14) SCL
//     PWM* (D6) PD6 20|        |21  PD7 (D7)  PWM
//                     +--------+
//
// PWM* not available on ATmega16 & ATmega32


// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
	PD, // PD 0 ** 0 ** USART0_RX
	PD, // PD 1 ** 1 ** USART0_TX
	PD, // PD 2 ** 2 ** USART1_RX
	PD, // PD 3 ** 3 ** USART1_TX
	PD, // PD 4 ** 4 ** PWM
	PD, // PD 5 ** 5 ** PWM
	PD, // PD 6 ** 6 ** PWM
	PD, // PD 7 ** 7 ** PWM
	PB, // PB 0 ** 8 ** D8
	PB, // PB 1 ** 9 ** D9
	PB, // PB 2 ** 10 ** D10
	PB, // PB 3 ** 11 ** PWM
	PB, // PB 4 ** 12 ** PWM/SPI_SS
	PB, // PB 5 ** 13 ** SPI_MOSI
	PC, // PC 0 ** 14 ** I2C_SCL
	PC, // PC 1 ** 15 ** I2C_SDA
	PC, // PC 2 ** 16 ** D16
	PC, // PC 3 ** 17 ** D17
	PC, // PC 4 ** 18 ** D18
	PC, // PC 5 ** 19 ** D19
   	PC, // PC 6 ** 20 ** D20
	PC, // PC 7 ** 21 ** D21
	PB, // PB 6 ** 22 ** SPI_MISO
	PB, // PB 7 ** 23 ** SPI_SCK
	PA, // PA 7 ** 24 ** A7
	PA, // PA 6 ** 25 ** A6
	PA, // PA 5 ** 26 ** A5
	PA, // PA 4 ** 27 ** A4
	PA, // PA 3 ** 28 ** A3
	PA, // PA 2 ** 29 ** A2
	PA, // PA 1 ** 30 ** A1
	PA  // PA 0 ** 31 ** A0
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
	_BV(0), // PD 0 ** 0 ** USART0_RX   
	_BV(1), // PD 1 ** 1 ** USART0_TX   
	_BV(2), // PD 2 ** 2 ** USART1_RX   
	_BV(3), // PD 3 ** 3 ** USART1_TX   
	_BV(4), // PD 4 ** 4 ** PWM         
	_BV(5), // PD 5 ** 5 ** PWM         
	_BV(6), // PD 6 ** 6 ** PWM         
	_BV(7), // PD 7 ** 7 ** PWM         
	_BV(0), // PB 0 ** 8 ** D8          
	_BV(1), // PB 1 ** 9 ** D9          
	_BV(2), // PB 2 ** 10 ** D10        
	_BV(3), // PB 3 ** 11 ** PWM        
	_BV(4), // PB 4 ** 12 ** PWM/SPI_SS 
	_BV(5), // PB 5 ** 13 ** SPI_MOSI   
	_BV(0), // PC 0 ** 14 ** I2C_SCL    
	_BV(1), // PC 1 ** 15 ** I2C_SDA    
	_BV(2), // PC 2 ** 16 ** D16        
	_BV(3), // PC 3 ** 17 ** D17        
	_BV(4), // PC 4 ** 18 ** D18        
	_BV(5), // PC 5 ** 19 ** D19        
	_BV(6), // PC 6 ** 20 ** D20        
	_BV(7), // PC 7 ** 21 ** D21        
	_BV(6), // PB 6 ** 22 ** SPI_MISO   
	_BV(7), // PB 7 ** 23 ** SPI_SCK    
	_BV(7), // PA 7 ** 24 ** A7         
	_BV(6), // PA 6 ** 25 ** A6         
	_BV(5), // PA 5 ** 26 ** A5         
	_BV(4), // PA 4 ** 27 ** A4         
	_BV(3), // PA 3 ** 28 ** A3         
	_BV(2), // PA 2 ** 29 ** A2         
	_BV(1), // PA 1 ** 30 ** A1         
	_BV(0)  // PA 0 ** 31 ** A0         
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
	NOT_ON_TIMER, // PD 0 ** 0 ** USART0_RX  
	NOT_ON_TIMER, // PD 1 ** 1 ** USART0_TX  
	NOT_ON_TIMER, // PD 2 ** 2 ** USART1_RX  
	NOT_ON_TIMER, // PD 3 ** 3 ** USART1_TX  
	TIMER1B,      // PD 4 ** 4 ** PWM        
	TIMER1A,      // PD 5 ** 5 ** PWM        
	TIMER2B,      // PD 6 ** 6 ** PWM        
	TIMER2A,      // PD 7 ** 7 ** PWM        
	NOT_ON_TIMER, // PB 0 ** 8 ** D8         
	NOT_ON_TIMER, // PB 1 ** 9 ** D9         
	NOT_ON_TIMER, // PB 2 ** 10 ** D10       
	TIMER0A,      // PB 3 ** 11 ** PWM       
	TIMER0B,      // PB 4 ** 12 ** PWM/SPI_SS
	NOT_ON_TIMER, // PB 5 ** 13 ** SPI_MOSI  
	NOT_ON_TIMER, // PC 0 ** 14 ** I2C_SCL   
	NOT_ON_TIMER, // PC 1 ** 15 ** I2C_SDA   
	NOT_ON_TIMER, // PC 2 ** 16 ** D16       
	NOT_ON_TIMER, // PC 3 ** 17 ** D17       
	NOT_ON_TIMER, // PC 4 ** 18 ** D18       
	NOT_ON_TIMER, // PC 5 ** 19 ** D19       
	NOT_ON_TIMER, // PC 6 ** 20 ** D20       
	NOT_ON_TIMER, // PC 7 ** 21 ** D21       
	NOT_ON_TIMER, // PB 6 ** 22 ** SPI_MISO  
	NOT_ON_TIMER, // PB 7 ** 23 ** SPI_SCK   
	NOT_ON_TIMER, // PA 7 ** 24 ** A7        
	NOT_ON_TIMER, // PA 6 ** 25 ** A6        
	NOT_ON_TIMER, // PA 5 ** 26 ** A5        
	NOT_ON_TIMER, // PA 4 ** 27 ** A4        
	NOT_ON_TIMER, // PA 3 ** 28 ** A3        
	NOT_ON_TIMER, // PA 2 ** 29 ** A2        
	NOT_ON_TIMER, // PA 1 ** 30 ** A1        
	NOT_ON_TIMER  // PA 0 ** 31 ** A0        
};

#endif

#endif