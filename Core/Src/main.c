#include "main.h"
#include "timer.h"

int main()
{
	TIM2_Init();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*) (GPIOD_BASE + 0x00);
	*GPIOD_MODER &= ~(0b11 << 30);
	*GPIOD_MODER |= 0b01 << 30;
	uint32_t* GPIOD_ODR = (uint32_t*) (GPIOD_BASE + 0x14);
	while (1)
	{
		*GPIOD_ODR |= 1 << 15;
		delay_ms(2000);
		*GPIOD_ODR &= ~(1 << 15);
		delay_ms(2000);
	}
	return 0;
}
