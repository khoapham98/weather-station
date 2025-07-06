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
	LCD_ClrScr();
	LCD_gotoxy(2, 1);
	LCD_print_String("%c'm Slee%c%c %c%c%c", 0xAA, 0xF0, 0xF9, 0xA5, 0x5E, 0xA5);

	while (1)
	{
		receive_data(data);
//		if (check_sum(data) == 1)
		{
//			LCD_ClrScr();
			delay_ms(200);
			LCD_gotoxy(1, 2);
			LCD_print_String_and_Scroll("HUMI: %d.%d %c, TEMP: %d.%d%cC", data[0], data[1], 0x25, data[2], data[3], 0xDF);
//			LCD_gotoxy(2, 1);
//			LCD_print_String("%c'm Slee%c%c %c%c%c", 0xAA, 0xF0, 0xF9, 0xA5, 0x5E, 0xA5);
		}

	}
	return 0;
}
