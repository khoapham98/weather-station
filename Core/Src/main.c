#include "main.h"
#include "timer.h"
#include "dht11.h"
#include "lcd1602.h"
#include "realtime_clock.h"
#include "uart.h"

uint8_t data[5] = { 0 };
time_t time;
date_t date;

int main()
{
	TIM2_Init();
	DHT11_Init();
	I2C1_Init();
	RTC_Init();
	UART_Init();
	LCD_Init();

	while (1)
	{
		time = get_time();
		date = get_date();
		LCD_gotoxy(2, 1);
		LCD_print_String("[Sleepy] %c %s %d%s, %d  -  %d:%02d:%02d", 0xA5, months[date.month - 1], date.day, date.suffix, date.year, time.hour, time.minute, time.second);
		receive_data(data);
		UART_SendDATA(data);
		if (check_sum(data) == 1)
		{
			LCD_gotoxy(1, 1);
			LCD_print_String("HUMI : %d.%d %cRH  -  TEMP : %d.%d %cC", data[0], data[1], 0x25, data[2], data[3], 0xDF);
		}
		scroll_left();
	}
	return 0;
}
