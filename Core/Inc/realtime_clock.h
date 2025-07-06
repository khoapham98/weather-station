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
uint32_t get_date();
uint32_t get_time();
void RTC_Init();
#endif /* INC_REALTIME_CLOCK_H_ */
