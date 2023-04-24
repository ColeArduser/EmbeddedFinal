#include "digital.h"

#define LOW     0
#define HIGH    1

#define DEV_BL_PIN_NUM 9

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(0), /* 14, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5)
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	0x00, /* 0 - pin 0 */
	0x00, /* 1 - pin 1 */
	0x00, /* 2 - pin 2 */
	0x2B, /* 3 - pin 3 */
	0x00, /* 4 - pin 4 */
	0x0B, /* 5 - pin 5 */
	0x0A, /* 6 - pin 6 */
	0x00, /* 7 - pin 7 */
	0x00, /* 8 - pin 8 */
	0x1A, /* 9 - pin 9 */
	0x1B, /* 10 - pin 10 */
	0x2A, /* 11 - pin 11 */
	0x00, /* 12 - pin 12 */
	0x00, /* 13 - pin 13 */
	0x00, /* 14 - pin A0 */
	0x00, /* 15 - pin A1 */
	0x00, /* 16 - pin A2 */
	0x00, /* 17 - pin A3 */
	0x00, /* 18 - pin A4 */
	0x00  /* 19 - pin A5 */
};


uint8_t digitalPinToPort(uint8_t pin) {
	if (pin >= 0 && pin <= 7) {
		return PORTD;
		} else if (pin >= 8 && pin <= 13) {
		return PORTB;
		} else if (pin >= 14 && pin <= 19) {
		return PORTC;
		} else {
		return 0;
	}
}

static void turnOffPWM(uint8_t timer)
{
	switch (timer)
	{
		case 0x0A:  TCCR0A &= ~(1 << COM0A1);    break;
		case 0x0B:  TCCR0A &= ~(1 << COM0B1);    break;
		case 0x1A:  TCCR1A &= ~(1 << COM1A1);    break;
		case 0x1B:  TCCR1A &= ~(1 << COM1B1);    break;
		case 0x2A:  TCCR2A &= ~(1 << COM2A1);    break;
		case 0x2B:  TCCR2A &= ~(1 << COM2B1);    break;
	}
}

void analogWrite(uint8_t pin, uint8_t value) {
	if (value == 0)
	{
		digitalWrite(pin, LOW);
	}
	else if (value == 255)
	{
		digitalWrite(pin, HIGH);
	}
	else
	{
		switch (pin) {
			case DEV_BL_PIN_NUM:
				TCCR1A |= (1 << COM1A1);
				OCR1A = value;
				break;
			default:
				if (value < 128) {
					digitalWrite(pin, LOW);
				}
				else {
					digitalWrite(pin, HIGH);
				}
		}
	}
}

uint8_t digitalRead(uint8_t pin)
{
	if (pin < 8) {
		// Read from the pin on PORTD
		return (PIND & (1 << pin)) >> pin;
		} else {
		// Read from the pin on PORTB
		return (PINB & (1 << (pin - 8))) >> (pin - 8);
	}
}


void digitalWrite(uint8_t pin, uint8_t value)
{
	uint8_t timer = pgm_read_byte(digital_pin_to_timer_PGM + pin);
	uint8_t bit = pgm_read_byte(digital_pin_to_bit_mask_PGM + pin);
	uint8_t port = digitalPinToPort(pin);

	if (port == 0) return;

	// If the pin that support PWM output, we need to turn it off
	// before doing a digital write.
	if (timer != 0) {
		turnOffPWM(timer);
	}

	uint8_t oldSREG = SREG;
	cli();

	if (value == LOW) {
		port &= ~bit;
		}
	else {
		port |= bit;
	}

	SREG = oldSREG;
}