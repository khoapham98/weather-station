/*
 * 	File		: realtime_clock.c
 *	Created on	: Jul 6, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */
#include "main.h"
#include "realtime_clock.h"
#include <string.h>

uint32_t get_date()
{
	uint32_t* RTC_DR  = (uint32_t*) (RTC_BASE_ADDR + 0x04);
	uint32_t* RTC_ISR  = (uint32_t*) (RTC_BASE_ADDR + 0x0C);
	while (((*RTC_ISR >> 5) & 1) == 0);
	return *RTC_DR;
}

uint32_t get_time()
{
	uint32_t* RTC_TR  = (uint32_t*) (RTC_BASE_ADDR + 0x00);
	uint32_t* RTC_ISR  = (uint32_t*) (RTC_BASE_ADDR + 0x0C);
	while (((*RTC_ISR >> 5) & 1) == 0);
	return *RTC_TR;
}

void RTC_Init()
{
	uint32_t* RTC_TR  = (uint32_t*) (RTC_BASE_ADDR + 0x00);
	uint32_t* RTC_DR  = (uint32_t*) (RTC_BASE_ADDR + 0x04);
	uint32_t* RTC_PRER = (uint32_t*) (RTC_BASE_ADDR + 0x10);
	uint32_t* RTC_ISR  = (uint32_t*) (RTC_BASE_ADDR + 0x0C);
	uint32_t* RTC_WPR  = (uint32_t*) (RTC_BASE_ADDR + 0x24);
	uint32_t* PWR_CR   = (uint32_t*) (PWR_BASE_ADDR + 0x00);
	uint32_t* RCC_APB1ENR = (uint32_t*) (RCC_BASE_ADDR + 0x40);
	uint32_t* RCC_BDCR = (uint32_t*) (RCC_BASE_ADDR + 0x70);
	uint32_t* RCC_CSR  = (uint32_t*) (RCC_BASE_ADDR + 0x74);

	/* enable write access to RTC registers */
	*RCC_APB1ENR |= 1 << 28;
	*PWR_CR |= 1 << 8;

	/* enable LSI crystal */
	*RCC_CSR |= 1 << 0;

	/* wait until LSI is ready */
	while (((*RCC_CSR >> 1) & 1) == 0);

	/* select LSI for RTC and enable RTC clock */
	*RCC_BDCR &= ~(0b11 << 8);
	*RCC_BDCR |= 0b10 << 8;
	*RCC_BDCR |= 1 << 15;

	/* unlock the write protection */
	*RTC_WPR = 0xCA;
	*RTC_WPR = 0x53;

	/* enter Init mode */
	*RTC_ISR |= 1 << 7;

	/* wait until RTC is in Init mode */
	while (((*RTC_ISR >> 6) & 1) == 0);

	/* configure ck_apre for calendar and ck_spre for sub secound counter */
	*RTC_PRER = (124 << 16) | 255;

	/* configure time and date for RTC */
	uint8_t time[6] = { 0 };
	update_time(time);
	*RTC_TR = (time[0] << 20) | (time[1] << 16) | (time[2] << 12) | (time[3] << 8) | (time[4] << 4) | time[5];

	uint8_t date[7] = { 0 };
	update_date(date);
//	*RTC_DR &= ~0xffff;
	*RTC_DR = (date[5] << 20) | (date[6] << 16) | ((date[0] / 10) << 12) | ((date[0] % 10) << 8) | (date[1] << 4) | date[2];

	/* exit the Init mode to finish the sequence */
	*RTC_ISR &= ~(1 << 7);

	/* re-active the write protection */
	*RTC_WPR = 0xFF;
}

char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

void update_date(uint8_t* date)
{
	char* DATE = __DATE__;
	int date_size = strlen(DATE);
	for (int i = 0; i < 12; i++)
	{
		if (strstr(DATE, months[i]) != NULL)
		{
			date[0] = ++i;
			break;
		}
	}

	int index = 1;
	for (int i = 3; i < date_size; i++)
	{
		if (DATE[i] >= '0' && DATE[i] <= '9')
		{
			date[index++] = DATE[i] - 48;
		}
	}
}

void update_time(uint8_t* time)
{
	char* TIME = __TIME__;
	int time_size = strlen(TIME);
	int index = 0;
	for (int i = 0; i < time_size; i++)
	{
		if (TIME[i] >= '0' && TIME[i] <= '9')
		{
			time[index++] = TIME[i] - 48;
		}
	}
}
