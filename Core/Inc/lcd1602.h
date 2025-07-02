/*
 * lcd1602.h
 *
 *  Created on: Jul 2, 2025
 *      Author: ACER
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

#define GPIOB_BASE_ADDR 0x40020400
#define I2C1_BASE_ADDR 0x40005400

typedef enum
{
	WRITE, READ
} mode_t;

void I2C1_Init();
void master_send(uint8_t slave_address, mode_t mode, uint8_t data);
#endif /* INC_LCD1602_H_ */
