#ifndef _DIGITAL_H_
#define _DIGITAL_H_

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/common.h>
#include <avr/interrupt.h>


uint8_t digitalPinToTimer(uint8_t pin);

uint8_t digitalPinToPort(uint8_t pin);

void analogWrite(uint8_t pin, uint8_t value);

uint8_t digitalRead(uint8_t pin);

void digitalWrite(uint8_t pin, uint8_t value);

#endif