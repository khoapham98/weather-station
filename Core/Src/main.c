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
	LCD_print_String("Date : %s, Time : %s", __DATE__, __TIME__);

	while (1)
	{
		receive_data(data);
		if (check_sum(data) == 1)
		{
			LCD_gotoxy(1, 1);
			LCD_print_String("HUMI : %d.%d %cRH  -  TEMP : %d.%d %cC", data[0], data[1], 0x25, data[2], data[3], 0xDF);
		}
		scroll_left();
	}
	return 0;
}
