#include "main.h"
#include "timer.h"
#include "dht11.h"
#include "lcd1602.h"
#include "realtime_clock.h"

uint8_t data[5] = { 0 };
uint32_t time;
uint32_t date;

int main()
{
	TIM2_Init();
	DHT11_Init();
	I2C1_Init();
	LCD_Init();
	RTC_Init();
	LCD_ClrScr();

	while (1)
	{
//		receive_data(data);
//		if (check_sum(data) == 1)
//		{
//			LCD_gotoxy(1, 1);
//			LCD_print_String("HUMI : %d.%d %cRH  -  TEMP : %d.%d %cC", data[0], data[1], 0x25, data[2], data[3], 0xDF);
//		}
//		scroll_left();
		time = get_time();
		date = get_date();
	}
	return 0;
}
