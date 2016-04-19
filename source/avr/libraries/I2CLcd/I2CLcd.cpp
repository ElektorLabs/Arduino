/**
* @file
* Implementation of an I2C LCD driver based on the ST7032i chip from Sitronix.
*
* Author: Clemens Valens
* License: GNU General Public License
*
* History
* 2014.09.08  ver 1.00    Preliminary version, first release
*/

#include "I2CLcd.h"


I2CLcd::I2CLcd(uint8_t resetPin, uint8_t backlightPin)
{
	m_backlightPin = backlightPin;
	pinMode(m_backlightPin,OUTPUT);
	backlight(false);

	// Reset LCD.
	m_resetPin = resetPin;
	pinMode(m_resetPin,OUTPUT);
	reset(false); // Assert reset pin.
}


void I2CLcd::begin(void)
{
	//int i;

	// Release LCD.
	delay(10);
	reset(true); // Deassert reset pin.
	delay(ST7032_RESET_RECOVERY_TIME);

	// Setup I2C port.
	Wire.begin(); // May be called more than once, so we can do it here too.

	// Initialize LCD module.
	// Set custom characters.
	/*for (i=0; i<8; i++)
	{
		setCustomCharacter(i,(const uint8_t *)&custom_characters[i]);
	}*/
	// Set our default config and enable extended functions.
	writeCommand(ST7032_CMD_FUNCTION,ST7032_FUNC_CONFIG_EXTENDED);
	// Set internal oscillator.
	writeCommand(ST7032_CMD_BIAS_OSC,ST7032_BIAS_020|4);
	// Set contrast. 4 is a good value for 3V displays.
	contrast(4);
	// Follower on, amplifier max. (Why? From the Midas datasheet)
	writeCommand(ST7032_CMD_FOLLOWER,ST7032_FOLLOWER_ON|7);
	// A 200 ms delay is recommended for the power to stabilize.
	delay(200);
	// Display on.
	//writeCommand(ST7032_CMD_ON_OFF,ST7032_DISPLAY_ON|ST7032_CURSOR_OFF|ST7032_BLINK_OFF);
	displayCursorBlink(1,0,0);
	// Clear display.
	clear();

	// Check custom characters.
	/*I2CLcd::displayCursorBlink(1,1,0);
	for (i=0; i<8; i++)
	{
		I2CLcd::putChar((char)i);
	}
	delay(5000);*/
}


uint8_t I2CLcd::putChar(char ch)
{
	writeData(ch);
	return 1;
}


uint8_t I2CLcd::putString(char const *p_str)
{
	uint8_t result = 0;

	while (*p_str!=0)
	{
		writeData(*p_str++);
		result += 1;
	}

	return result;
}


void I2CLcd::clear(void)
{
	writeCommand(ST7032_CMD_CLEAR,0);
	delay(2);
}


void I2CLcd::cursorMove(uint8_t line, uint8_t column)
{
	writeCommand(ST7032_CMD_DDRAM_ADDRESS,(line==0?0:0x40)+column);
	displayCursorBlink(1,0,0);
}


void I2CLcd::cursor(uint8_t line, uint8_t column)
{
	writeCommand(ST7032_CMD_DDRAM_ADDRESS,(line==0?0:0x40)+column);
	displayCursorBlink(1,0,0);
}


void I2CLcd::displayCursorBlink(uint8_t display, uint8_t cursor, uint8_t blink)
{
	uint8_t cmd = 0;
	if (display!=0) cmd |= ST7032_DISPLAY_ON;
	// Beware of auto-increment. If you don't see the cursor, maybe it fell off the screen?
	if (cursor!=0) cmd |= ST7032_CURSOR_ON;
	if (blink!=0) cmd |= ST7032_BLINK_ON;
	writeCommand(ST7032_CMD_ON_OFF,cmd);
}


void I2CLcd::clearToEol(int line, int column)
{
	uint8_t i;
	cursorMove(line,column);
	for (i=column; i<ST7032_CHARS_PER_LINE; i++)
	{
		putChar(' ');
	}
	cursorMove(line,column);
}


void I2CLcd::contrast(uint8_t contrast)
{
	// Set contrast low bits.
	writeCommand(ST7032_CMD_CONTRAST_LO,contrast&ST7032_CONTRAST_LO_MASK);
	// Set contrast high bits.
	// When LCD is powered from 3V the booster must be on.
	writeCommand(ST7032_CMD_POWER_ICON_CONTRAST,ST7032_BOOSTER_ON|((contrast>>4)&ST7032_CONTRAST_HI_MASK));
}


void I2CLcd::font(uint8_t font)
{
	writeCommand(ST7032_CMD_FUNCTION,ST7032_FUNC_CONFIG_EXTENDED|(font&ST7032_FUNC_HEIGHT_DOUBLE));
}


void I2CLcd::setCustomCharacter(uint8_t index, const uint8_t *p_data)
{
	int i;
	// Up to 8 custom characters may be defined.
	// Select function table 0.
	writeCommand(ST7032_CMD_FUNCTION,ST7032_FUNC_CONFIG_NORMAL);
	// Set CGRAM address.
	writeCommand(ST7032_CMD_CGRAM_ADDRESS,(8*index)&0x3f);
	// 8 bytes per character.
	for (i=0; i<7; i++)
	{
		writeData(p_data[i]&0x1f);
	}
}


void I2CLcd::bargraph(uint8_t position, uint8_t value, uint8_t value_max)
{
	//writeCommand(ST7032_CMD_ON_OFF,ST7032_DISPLAY_ON|ST7032_CURSOR_OFF|ST7032_BLINK_OFF);
	uint16_t v = value;
	v = 14*v/value_max; // map [1,255] to 14 possibilities, 0 is possibility 15.
	cursor(1,position);
	if (v<=6)
	{
		if (value==0)
		{
			v = 5; //'0';
		}
		else
		{
			v += 1;
			if (v==5) v = 0x11;
			else if (v==7) v = 'T';
		}
		putChar(v);
		cursor(0,position);
		putChar(0);
	}
	else
	{
		putChar(0);
		cursor(0,position);
		v -= 6;
		if (v==5) v = 0x11;
		else if (v==7) v = 'T';
		else if (v>7) v = 7; //'M';
		putChar(v);
	}
}
