#include "main.h"
#include "timer.h"
#include "dht11.h"
#include "lcd1602.h"
#include "realtime_clock.h"

uint8_t data[5] = { 0 };
time_t time;
date_t date;

int main()
{
//	DHT11_Init();
	TIM2_Init();
	I2C1_Init();
	LCD_Init();
	LCD_ClrScr();
	RTC_Init();

	while (1)
	{
//		receive_data(data);
//		if (check_sum(data) == 1)
//		{
//			LCD_gotoxy(1, 1);
//			LCD_print_String("HUMI : %d.%d %cRH  -  TEMP : %d.%d %cC", data[0], data[1], 0x25, data[2], data[3], 0xDF);
//		}
		time = get_time();
		date = get_date();
		LCD_gotoxy(2, 1);
		LCD_print_String("%s %d%s, %d  -  %d:%02d:%02d", months[date.month - 1], date.day, date.suffix, date.year, time.hour, time.minute, time.second);
		scroll_left();

	}
	return 0;
}
