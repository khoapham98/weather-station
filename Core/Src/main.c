#include "main.h"
#include "timer.h"
#include "dht11.h"
#include "lcd1602.h"

uint8_t data[5] = { 0 };
char data_correct = 0;

int main()
{
	TIM2_Init();
	DHT11_Init();
	I2C1_Init();
	LCD_Init();

	while (1)
	{
		LCD_printString("Pham Anh Khoa");
 		delay_ms(3000);
 		LCD_ClrScr();
 		delay_ms(1000);
	}
	return 0;
}
