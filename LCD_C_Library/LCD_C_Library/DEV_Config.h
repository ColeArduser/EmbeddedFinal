/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdint.h>
#include <stdio.h>
#include "SPI.h"
#include "digital.h"
#include "Debug.h"
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <avr/common.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define LOW     0
#define HIGH    1

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define DEV_CS_PIN  PINB2
#define DEV_DC_PIN  PIND7
#define DEV_RST_PIN PINB0
#define DEV_BL_PIN  PINB1

#define DEV_CS_PIN_NUM  10
#define DEV_DC_PIN_NUM  7
#define DEV_RST_PIN_NUM 8
#define DEV_BL_PIN_NUM  9


/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_Digital_Read(_pin) digitalRead(_pin)


/**
 * SPI
**/
#define DEV_SPI_WRITE(_dat)   SPI_transfer(_dat)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms)    _delay_ms(__xms)

/**
 * PWM_BL
**/
 #define  DEV_Set_PWM(_Value)  analogWrite(DEV_BL_PIN_NUM, _Value)

/*-----------------------------------------------------------------------------*/
 void Config_Init();
#endif
