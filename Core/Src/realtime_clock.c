/*
 * 	File		: realtime_clock.c
 *	Created on	: Jul 6, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */
#include "main.h"
#include "realtime_clock.h"

uint32_t get_date()
{
	uint32_t* RTC_TR  = (uint32_t*) (RTC_BASE_ADDR + 0x00);
	uint32_t* RTC_ISR  = (uint32_t*) (RTC_BASE_ADDR + 0x0C);
	while (((*RTC_ISR >> 5) & 1) == 0);
	return *RTC_TR;
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

	/* exit the Init mode to finish the sequence */
	*RTC_ISR &= ~(1 << 7);

	/* re-active the write protection */
	*RTC_WPR = 0xFF;
}

