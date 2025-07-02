/*
 * dht11.c
 *
 *  Created on: Jul 1, 2025
 *      Author: ACER
 */
#include "main.h"
#include "dht11.h"
#include "timer.h"

char check_sum(uint8_t* data)
{
	uint8_t* checksum = &data[0] + 4;
	uint8_t sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += data[i];
	}

	return (sum == (*checksum)) ? 1 : 0;
}

void receive_data(uint8_t* data)
{
	uint32_t* GPIOC_MODER = (uint32_t*) (GPIOC_BASE_ADDR + 0x00);
	uint32_t* GPIOC_ODR = (uint32_t*) (GPIOC_BASE_ADDR + 0x14);
	uint32_t* GPIOC_IDR = (uint32_t*) (GPIOC_BASE_ADDR + 0x10);

	/* Set PC14 as OUTPUT */
	*GPIOC_MODER &= ~(0b11 << (14 * 2));
	*GPIOC_MODER |= (0b01 << (14 * 2));

	/* MCU pulls down voltage for at least 18ms */
	*GPIOC_ODR &= ~(1 << 14);
	delay_ms(25);

	/* MCU pulls up voltage and wait for DHT response (~20us) */
	*GPIOC_ODR |= 1 << 14;
	delay_us(30);

	/* Set PC14 as INPUT to receive the response from DHT11 */
	*GPIOC_MODER &= ~(0b11 << (14 * 2));

	/* wait for DHT11 to response */
	while (((*GPIOC_IDR >> 14) & 1) == 1);
	delay_us(70);
	while (((*GPIOC_IDR >> 14) & 1) == 0);
	delay_us(70);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			while (((*GPIOC_IDR >> 14) & 1) == 1);
			delay_us(40);
			while (((*GPIOC_IDR >> 14) & 1) == 0);
			delay_us(30);

			if (((*GPIOC_IDR >> 14) & 1) == 1)
			{
				data[i] |= (1 << j);
			}
		}
	}
	delay_us(50);
}

/*
	VCC: 3V
	DATA: PC14
	GND: GND
 */
void DHT11_Init()
{
	delay_ms(2000);
	__HAL_RCC_GPIOC_CLK_ENABLE();
	uint32_t* GPIOC_MODER = (uint32_t*) (GPIOC_BASE_ADDR + 0x00);
	uint32_t* GPIOC_ODR = (uint32_t*) (GPIOC_BASE_ADDR + 0x14);

	/* Set PC14 as OUTPUT */
	*GPIOC_MODER &= ~(0b11 << (14 * 2));
	*GPIOC_MODER |= (0b01 << (14 * 2));

	/* pull up voltage to work at free status */
	*GPIOC_ODR |= 1 << 14;
}
