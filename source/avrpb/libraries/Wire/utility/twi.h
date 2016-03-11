/*
  twi.h - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2016 by Clemens Valens (labs@elektor.com) to add multi-peripheral support.
*/

#ifndef twi_h
#define twi_h

#include <inttypes.h>

//#define ATMEGA8

#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 32
#endif

#define TWI_READY 0
#define TWI_MRX   1
#define TWI_MTX   2
#define TWI_SRX   3
#define TWI_STX   4

typedef struct
{
  volatile uint8_t *twbr; // bit rate register
  volatile uint8_t *twsr; // status register
  volatile uint8_t *twar; // (slave) address register
  volatile uint8_t *twdr; // data register
  volatile uint8_t *twcr; // control register
  volatile uint8_t *twamr; // (slave) address mask register
  uint8_t sda; // SDA pin
  uint8_t scl; // SCL pin
  volatile uint8_t state;
  volatile uint8_t slarw;
  volatile uint8_t sendStop;			// should the transaction end with a stop
  volatile uint8_t inRepStart;			// in the middle of a repeated start
  void (*onSlaveTransmit)(void);
  void (*onSlaveReceive)(uint8_t*, int);
  uint8_t masterBuffer[TWI_BUFFER_LENGTH];
  volatile uint8_t masterBufferIndex;
  volatile uint8_t masterBufferLength;
  uint8_t txBuffer[TWI_BUFFER_LENGTH];
  volatile uint8_t txBufferIndex;
  volatile uint8_t txBufferLength;
  uint8_t rxBuffer[TWI_BUFFER_LENGTH];
  volatile uint8_t rxBufferIndex;
  volatile uint8_t error;
}
twi_descriptor_t;

extern twi_descriptor_t TWI0;
extern twi_descriptor_t TWI1;

// Register bit values are identical for TWI0 and TWI1.
// status register bits
#define TWPS0  TWPS00
#define TWPS1  TWPS01
#define TWS3  TWS03 
#define TWS4  TWS04 
#define TWS5  TWS05 
#define TWS6  TWS06 
#define TWS7  TWS07 
// (slave) address register bits
#define TWGCE  TWGCE0
#define TWA0  TWA00 
#define TWA1  TWA01 
#define TWA2  TWA02 
#define TWA3  TWA03 
#define TWA4  TWA04 
#define TWA5  TWA05 
#define TWA6  TWA06 
// control register bits
#define TWIE  TWIE0 
#define TWEN  TWEN0 
#define TWWC  TWWC0 
#define TWSTO  TWSTO0
#define TWSTA  TWSTA0
#define TWEA  TWEA0 
#define TWINT  TWINT0
// (slave) address mask register bits
#define TWAM0  TWAM00
#define TWAM1  TWAM01
#define TWAM2  TWAM02
#define TWAM3  TWAM03
#define TWAM4  TWAM04
#define TWAM5  TWAM05
#define TWAM6  TWAM06

void twi_init_twi0(void);
void twi_init_twi1(void);
void twi_init(twi_descriptor_t *p_twi);
void twi_disable(twi_descriptor_t *p_twi);
void twi_setAddress(twi_descriptor_t *p_twi, uint8_t);
uint8_t twi_readFrom(twi_descriptor_t *p_twi, uint8_t, uint8_t*, uint8_t, uint8_t);
uint8_t twi_writeTo(twi_descriptor_t *p_twi, uint8_t, uint8_t*, uint8_t, uint8_t, uint8_t);
uint8_t twi_transmit(twi_descriptor_t *p_twi, const uint8_t*, uint8_t);
void twi_attachSlaveRxEvent(twi_descriptor_t *p_twi, void (*)(uint8_t*, int) );
void twi_attachSlaveTxEvent(twi_descriptor_t *p_twi, void (*)(void) );
void twi_reply(twi_descriptor_t *p_twi, uint8_t);
void twi_stop(twi_descriptor_t *p_twi);
void twi_releaseBus(twi_descriptor_t *p_twi);

#endif /* twi_h */

