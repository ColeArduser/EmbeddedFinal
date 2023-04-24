#include "SPI.h"
#include "digital.h"

#define SS 10


const uint16_t PROGMEM port_to_mode_PGM[] = {
	0x00,
	0x00,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};


void SPI_begin() {
	uint8_t sreg = SREG;
	cli();
	
	uint8_t port = PORTB;
	uint8_t bit = _BV(2);
	volatile uint8_t *reg = (volatile uint8_t *)pgm_read_word( port_to_mode_PGM[port]);
	
	if(!(*reg & bit)){
		digitalWrite(SS, 1);
	}
	
	DDRB |= (1 << PINB2);
	
	SPCR |= _BV(MSTR);
	SPCR |= _BV(SPE);
	
	DDRB |= (1 << PINB5) | (1 << PINB3);
	
	SREG = sreg;
}

uint8_t SPI_transfer(uint8_t data) {
	SPDR = data;
  
    asm volatile("NOP");
    while (!(SPSR & _BV(SPIF))) ; // wait
    return SPDR;
}