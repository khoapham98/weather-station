/*
 * 	File		: realtime_clock.h
 *	Created on	: Jul 6, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */

#ifndef INC_REALTIME_CLOCK_H_
#define INC_REALTIME_CLOCK_H_

#define RTC_BASE_ADDR 0x40002800
#define PWR_BASE_ADDR 0x40007000
#define RCC_BASE_ADDR 0x40023800

extern char* months[12];

typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} time_t;

typedef struct
{
	uint8_t day;
	char* suffix;
	uint8_t month;
	uint16_t year;
} date_t;

void update_date(uint8_t* date);
void update_time(uint8_t* time);
date_t get_date();
time_t get_time();
void RTC_Init();
#endif /* INC_REALTIME_CLOCK_H_ */
