#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/common.h>
#include <avr/interrupt.h>

#define SPI_MODE 0x0C
#define SPI_MODE_MASK 0x0C
#define SPI_CLOCK_DIV 0x04
#define SPI_CLOCK_MASK 0x03
#define SPI_2XCLOCK_MASK 0x01


void SPI_begin();
uint8_t SPI_transfer(uint8_t data);

inline void SPI_setDataMode() {
	SPCR = (SPCR & ~SPI_MODE_MASK) | SPI_MODE;
}

inline void SPI_setBitOrder() {
	SPCR &= ~(1 << DORD);
}

inline void SPI_setClockDivider() {
	SPCR = (SPCR & ~SPI_CLOCK_MASK) | (SPI_CLOCK_DIV & SPI_CLOCK_MASK);
	SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((SPI_CLOCK_DIV >> 2) & SPI_2XCLOCK_MASK);
}

#endif