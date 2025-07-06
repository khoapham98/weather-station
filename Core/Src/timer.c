/*
 * 	File		: timer.c
 *	Created on	: Jul 1, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */
#include "main.h"
#include "timer.h"

void delay_ms(uint32_t ms)
{
	uint32_t* TIM2_CNT = (uint32_t*) (TIM2_BASE_ADDR + 0x24);
	uint32_t time = ms * 1000;
	*TIM2_CNT = 0;
	while (*TIM2_CNT < time);
}

void delay_us(uint16_t us)
{
	uint16_t* TIM2_CNT = (uint16_t*) (TIM2_BASE_ADDR + 0x24);
	*TIM2_CNT = 0;
	while (*TIM2_CNT < us);
}

/*
	TIMER 2 CHANNEL 2
 */
void TIM2_Init()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	uint16_t* TIM2_CR1 = (uint16_t*) (TIM2_BASE_ADDR + 0x00);
	uint16_t* TIM2_PSC = (uint16_t*) (TIM2_BASE_ADDR + 0x28);
	uint32_t* TIM2_ARR = (uint32_t*) (TIM2_BASE_ADDR + 0x2C);
	uint16_t* TIM2_CNT = (uint16_t*) (TIM2_BASE_ADDR + 0x24);
	uint16_t* TIM2_EGR = (uint16_t*) (TIM2_BASE_ADDR + 0x14);

	/* Counter used as up-counter */
	*TIM2_CR1 &= ~(1 << 4);

	/* set TIMER2 freq = 1MHz */
	*TIM2_PSC = 15;

	/* set TIMER2 */
	*TIM2_ARR = 0xffffffff;

	/* Reset counter value */
	*TIM2_CNT = 0;

	*TIM2_EGR |= 1 << 0;

	/* Enable counter */
	*TIM2_CR1 |= 1 << 0;
}
