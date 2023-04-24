#include "SPI.h"
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

#define LOW     0
#define HIGH    1


void wiring_init()
{
	ISR(TIMER0_OVF_vect);
	sei();

	TCCR0A = (1 << WGM01) | (1 << WGM00);
	TCCR0B = (1 << CS01) | (1 << CS00);
	TIMSK0 = (1 << TOIE0);


	TCCR1B = 0;
	TCCR1B = (1 << CS11) | (1 << CS10);

	TCCR1A = (1 << WGM10);
	TCCR2B = (1 << CS22);

	TCCR2A = (1 << WGM20);

	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);

	UCSR0B = 0;
}

void setup()
{
	Config_Init();
	LCD_Init();
	LCD_Clear(0xffff);
	Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
	Paint_Clear(WHITE);
	Paint_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);
	Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
  
  
	Paint_DrawRectangle(125, 10, 225, 58, RED,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawLine(125, 10, 225, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine(225, 10, 125, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  
	Paint_DrawCircle(150,100, 25, BLUE,   DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(180,100, 25, BLACK,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(210,100, 25, RED,    DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(165,125, 25, YELLOW, DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
	Paint_DrawCircle(195,125, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  
  
	//Paint_DrawFloatNum (5, 150 ,987.654321,4,  &Font20,    WHITE,   LIGHTGREEN);

}
void loop()
{
  
}

int main() {
	wiring_init();
	setup();
	while(1);
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
