/*
 * lcd1602.c
 *
 *  Created on: Jul 2, 2025
 *      Author: ACER
 */
#include "main.h"
#include "lcd1602.h"
#include "timer.h"

void LCD_Init()
{
	/* after power on, wait for more than 40ms after VCC rises to 2.7 V */
	delay_ms(50);

	/* function set */
	master_funcSet(0b0011);
	delay_ms(5);
	master_funcSet(0b0011);
	delay_us(110);
	master_funcSet(0b0011);
	delay_us(110);
	master_funcSet(0b0010);
	delay_us(110);

	/* select 4-bit operation */
	master_sendCMD(0x28);
	delay_us(40);

	/* Display Off */
	master_sendCMD(0x08);
	delay_us(40);

	/* clear display */
	master_sendCMD(0x01);
	delay_ms(2);

	/* entry mode set */
	master_sendCMD(0x06);
	delay_us(40);

	/* Display ON */
	master_sendCMD(0xE);
	delay_us(40);
}

void master_funcSet(uint8_t data)
{
	uint16_t* I2C_CR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x00);
	uint16_t* I2C_SR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x14);
	uint16_t* I2C_SR2 = (uint16_t*) (I2C1_BASE_ADDR + 0x18);
	uint16_t* I2C_DR  = (uint16_t*) (I2C1_BASE_ADDR + 0x10);

	/* wait until bus is free */
	while (((*I2C_SR2 >> 1) & 1) == 1);

	/* generate START condition */
	*I2C_CR1 |= 1 << 8;

	/* wait for START condition is generated */
	while ((*I2C_SR1 & 1) == 0);

	/* send slave address */
	volatile uint16_t tmp = *I2C_SR1;
	*I2C_DR = (0x27 << 1) | WRITE;

	/* wait until the slave address is sent and slave response ACK */
	while (((*I2C_SR1 >> 1) & 1) == 0);
	tmp = *I2C_SR1;
	tmp = *I2C_SR2;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);

	/* send data or instruction */
	*I2C_DR = (data << 4) | CMD;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);

	/* clear bit EN */
	delay_us(10);
	*I2C_DR = (data << 4) | 0b1000;

	/* wait until the Data register is empty and transfer finished */
	while ((((*I2C_SR1 >> 7) & 1) == 0) && (((*I2C_SR1 >> 2) & 1) == 0));

	/* generate STOP condition */
	*I2C_CR1 |= 1 << 9;
}

void master_sendDATA(uint8_t data)
{
	uint16_t* I2C_CR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x00);
	uint16_t* I2C_SR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x14);
	uint16_t* I2C_SR2 = (uint16_t*) (I2C1_BASE_ADDR + 0x18);
	uint16_t* I2C_DR  = (uint16_t*) (I2C1_BASE_ADDR + 0x10);

	/* wait until bus is free */
	while (((*I2C_SR2 >> 1) & 1) == 1);

	/* generate START condition */
	*I2C_CR1 |= 1 << 8;

	/* wait for START condition is generated */
	while ((*I2C_SR1 & 1) == 0);

	/* send slave address */
	volatile uint16_t tmp = *I2C_SR1;
	*I2C_DR = (0x27 << 1) | WRITE;

	/* wait until the slave address is sent and slave response ACK */
	while (((*I2C_SR1 >> 1) & 1) == 0);
	tmp = *I2C_SR1;
	tmp = *I2C_SR2;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);

	/* send data or instruction */
	uint8_t high_bits = data >> 4;
	*I2C_DR = (high_bits << 4) | DATA;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);
	delay_us(10);

	/* clear bit EN */
	*I2C_DR = (high_bits << 4) | 0b1001;

	/* send data or instruction */
	uint8_t low_bits = data;
	*I2C_DR = (low_bits << 4) | DATA;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);
	delay_us(10);

	/* clear bit EN */
	*I2C_DR = (low_bits << 4) | 0b1001;

	/* wait until the Data register is empty and transfer finished */
	while ((((*I2C_SR1 >> 7) & 1) == 0) && (((*I2C_SR1 >> 2) & 1) == 0));

	/* generate STOP condition */
	*I2C_CR1 |= 1 << 9;
}

void master_sendCMD(uint8_t data)
{
	uint16_t* I2C_CR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x00);
	uint16_t* I2C_SR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x14);
	uint16_t* I2C_SR2 = (uint16_t*) (I2C1_BASE_ADDR + 0x18);
	uint16_t* I2C_DR  = (uint16_t*) (I2C1_BASE_ADDR + 0x10);

	/* wait until bus is free */
	while (((*I2C_SR2 >> 1) & 1) == 1);

	/* generate START condition */
	*I2C_CR1 |= 1 << 8;

	/* wait for START condition is generated */
	while ((*I2C_SR1 & 1) == 0);

	/* send slave address */
	volatile uint16_t tmp = *I2C_SR1;
	*I2C_DR = (0x27 << 1) | WRITE;

	/* wait until the slave address is sent and slave response ACK */
	while (((*I2C_SR1 >> 1) & 1) == 0);
	tmp = *I2C_SR1;
	tmp = *I2C_SR2;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);

	/* send data or instruction */
	uint8_t high_bits = data >> 4;
	*I2C_DR = (high_bits << 4) | CMD;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);
	delay_us(10);

	/* clear bit EN */
	*I2C_DR = (high_bits << 4) | 0b1000;

	/* send data or instruction */
	uint8_t low_bits = data;
	*I2C_DR = (low_bits << 4) | CMD;

	/* wait until the Data register is empty */
	while (((*I2C_SR1 >> 7) & 1) == 0);
	delay_us(10);

	/* clear bit EN */
	*I2C_DR = (low_bits << 4) | 0b1000;

	/* wait until the Data register is empty and transfer finished */
	while ((((*I2C_SR1 >> 7) & 1) == 0) && (((*I2C_SR1 >> 2) & 1) == 0));

	/* generate STOP condition */
	*I2C_CR1 |= 1 << 9;
}

/*	==  I2C1  ==
	VCC: 3V
	GND: GND
	PB8: SCL
	PB9: SDA
 */
void I2C1_Init()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	uint32_t* GPIOB_MODER = (uint32_t*) (GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_AFRH = (uint32_t*) (GPIOB_BASE_ADDR + 0x24);
	uint32_t* GPIOB_OTYPER = (uint32_t*) (GPIOB_BASE_ADDR + 0x04);

	/* Configure PB8 & PB9 at AF */
	*GPIOB_MODER &= ~(0xf << (8 * 2));
	*GPIOB_MODER |= (0b10 << (8 * 2)) | (0b10 << (9 * 2));

	*GPIOB_OTYPER |= (1 << 8) | (1 << 9);

	/* Select AF04 */
	*GPIOB_AFRH &= ~(0xff << 0);
	*GPIOB_AFRH |= (4 << 0) | (4 << 4);

	__HAL_RCC_I2C1_CLK_ENABLE();
	uint16_t* I2C_CR1 = (uint16_t*) (I2C1_BASE_ADDR + 0x00);
	uint16_t* I2C_CR2 = (uint16_t*) (I2C1_BASE_ADDR + 0x04);
	uint16_t* I2C_CCR = (uint16_t*) (I2C1_BASE_ADDR + 0x1C);
	uint16_t* I2C_TRISE = (uint16_t*) (I2C1_BASE_ADDR + 0x20);

	/* configure I2C clock frequency = 16MHz */
	*I2C_CR2 |= 16 << 0;

	/* configure SCL to generate 100kHz */
	*I2C_CCR = 80;

	/* Set rise time */
	*I2C_TRISE = 16 + 1;

	/* enable I2C */
	*I2C_CR1 |= 1 << 0;
}
