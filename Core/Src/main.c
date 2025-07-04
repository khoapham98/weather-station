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
		receive_data(data);
		if (check_sum(data) == 1)
		{
			LCD_ClrScr();
			delay_ms(200);
			LCD_gotoxy(1, 1);
			LCD_printString("Humi: %d.%d %c", data[0], data[1], 0x25);
			LCD_gotoxy(2, 1);
			LCD_printString("Temp: %d.%d %cC", data[2], data[3], 0xDF);
			delay_ms(1000);
		}
		delay_ms(1000);
	}
	return 0;
}
