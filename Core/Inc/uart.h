/*
 * 	File		: uart.h
 *	Created on	: Jul 8, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#define GPIOB_BASE_ADDR 0x40020400
#define UART1_BASE_ADDR 0x40011000
void UART_Send4Bytes(uint8_t* _data);
void UART_SendByte(uint8_t data);
void UART_Init();
#endif /* INC_UART_H_ */
