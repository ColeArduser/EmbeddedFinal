#include "DEV_Config.h"

void GPIO_Init()
{
	DDRB |= (1 << DEV_CS_PIN) | (1 << DEV_RST_PIN) | (1 << DEV_BL_PIN);
	DDRD |= (1 << DEV_DC_PIN);
	analogWrite(DEV_BL_PIN_NUM,140);
}
void Config_Init()
{
	GPIO_Init();
	
	//Serial
	//Serial.begin(115200);
	UBRR0H = (unsigned char)(0x0000 >> 8); // set the baud rate to 115200
	UBRR0L = (unsigned char)(0x0000);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable receiver and transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // set frame format: 8 data bits, no parity, 1 stop bit

	//spi
	SPI_setDataMode();
	SPI_setBitOrder();
	SPI_setClockDivider();
	SPI_begin();
}
