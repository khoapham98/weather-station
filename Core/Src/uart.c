/*
 * 	File		: uart.c
 *	Created on	: Jul 8, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */
#include "main.h"
#include "uart.h"

void UART_SendDATA(uint8_t* _data)
{
	UART_SendByte(START_BYTE);
	for (int i = 0; i < 4; i++)
	{
		UART_SendByte(_data[i]);
	}
	UART_SendByte(STOP_BYTE);
}

void UART_SendByte(uint8_t data)
{
	uint32_t* UART_SR = (uint32_t*) (UART1_BASE_ADDR + 0x00);
	uint32_t* UART_DR = (uint32_t*) (UART1_BASE_ADDR + 0x04);

	/* send data */
	*UART_DR = data;

	/* wait until the transmission is completed */
	while (((*UART_SR >> 7) & 1) == 0);
}

/*
	PB6: UART1 TX
	Parity: even
	baud rate: 9600 bps
 */
void UART_Init()
{
	uint32_t* GPIOB_MODER = (uint32_t*) (GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_AFRL  = (uint32_t*) (GPIOB_BASE_ADDR + 0x20);

	/* configure PB6 as AF */
	*GPIOB_MODER &= ~(0b11 << (6 * 2));
	*GPIOB_MODER |=  (0b10 << (6 * 2));

	/* select AF07 for PB6 */
	*GPIOB_AFRL &= ~(0xf << (6 * 4));
	*GPIOB_AFRL |=  (7 << (6 * 4));

	__HAL_RCC_USART1_CLK_ENABLE();
	uint32_t* UART_CR1 = (uint32_t*) (UART1_BASE_ADDR + 0x0C);
	uint32_t* UART_BRR = (uint32_t*) (UART1_BASE_ADDR + 0x08);

	/* select word length = 9 data bits */
	*UART_CR1 |= 1 << 12;

	/* enable even parity bit */
	*UART_CR1 |= 1 << 10;

	/* enable transmitter */
	*UART_CR1 |= 1 << 3;

	/* configure baud rate = 9600 bps */
	*UART_BRR = (104 << 4) | (3 << 0);

	/* enable UART */
	*UART_CR1 |= 1 << 13;
}

