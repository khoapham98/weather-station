/*
 * lcd1602.c
 *
 *  Created on: Jul 2, 2025
 *      Author: ACER
 */
#include "main.h"
#include "lcd1602.h"
#include "timer.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*
	1 <= row <= 2
	1 <= column <= 40
 */
void LCD_gotoxy(uint8_t row, uint8_t column)
{
	if (row == 1)
	{
		set_cursor_position((column - 1) * row);
	}
	else if (row == 2)
	{
		set_cursor_position(column + 63);
	}
	else
	{
		LCD_gotoxy(1, 1);
		LCD_print_String("INVALID NUMBER");
		LCD_gotoxy(2, 1);
		LCD_print_String("BACK TO 1ST LINE");
		delay_ms(3000);
		LCD_ClrScr();
	}
}

void set_cursor_position(uint8_t cmd)
{
	LCD_WriteCMD(cmd | POS);
	delay_us(40);
}

void scroll_left()
{
	for (int i = 0; i < 16; i++)
	{
		delay_ms(300);
		LCD_WriteCMD(0x18);
	}
}

void LCD_print_String(char* str, ...)
{
	va_list list;
	va_start(list, str);
	char print_buf[128] = { 0 };
	vsprintf(print_buf, str, list);
	int size = strlen(print_buf);
	for (int i = 0; i < size; i++)
	{
		LCD_print_Char(print_buf[i]);
	}
	va_end(list);
}

void LCD_print_Char(uint8_t ch)
{
	LCD_WriteDATA(ch);
	delay_us(40);
}

void LCD_ClrScr()
{
	/* clear display */
	LCD_WriteCMD(0x01);
	delay_ms(2);

	/* return home */
	LCD_WriteCMD(0x02);
	delay_ms(2);
}

void LCD_WriteDATA(uint8_t data)
{
	uint8_t high_bits = data & 0xF0;
	uint8_t low_bits = data << 4;
	write_4bits(high_bits | DATA);
	write_4bits(low_bits | DATA);
}

void LCD_WriteCMD(uint8_t data)
{
	uint8_t high_bits = data & 0xF0;
	uint8_t low_bits = data << 4;
	write_4bits(high_bits | CMD);
	write_4bits(low_bits | CMD);
}

void write_4bits(uint8_t data)
{
	/* make sure EN bit is low before send new data */
	master_transmit(data & ~ENABLE);
	delay_us(25);

	/* send data with EN = 1 and EN = 0*/
	master_transmit(data | ENABLE);
	delay_us(25);
	master_transmit(data & ~ENABLE);
	delay_us(25);
}

void master_transmit(uint8_t data)
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
	*I2C_DR = data | BACKLIGHT;

	/* wait until the Data register is empty and transfer finished */
	while ((((*I2C_SR1 >> 7) & 1) == 0) && (((*I2C_SR1 >> 2) & 1) == 0));

	/* generate STOP condition */
	*I2C_CR1 |= 1 << 9;
}

void LCD_Init()
{
	/* after power on, wait for more than 40ms after VCC rises to 2.7 V */
	delay_ms(50);

	/* function set */
	write_4bits(0x03 << 4);
	delay_ms(5);
	write_4bits(0x03 << 4);
	delay_us(110);
	write_4bits(0x03 << 4);
	delay_us(110);
	write_4bits(0x02 << 4);
	delay_us(110);

	/* select 4-bit operation and select 2 line display */
	LCD_WriteCMD(0x28);
	delay_us(40);

	/* Display ON & display cursor */
	LCD_WriteCMD(0x0C);
	delay_us(40);

	/* clear display */
	LCD_WriteCMD(0x01);
	delay_ms(2);

	/* entry mode set */
	LCD_WriteCMD(0x06);
	delay_us(40);

	/* display shift to the right */
	LCD_WriteCMD(0x1C);
	delay_us(40);

	/* return home */
	LCD_WriteCMD(0x02);
	delay_ms(2);
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
