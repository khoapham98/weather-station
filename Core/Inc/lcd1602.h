/*
 * lcd1602.h
 *
 *  Created on: Jul 2, 2025
 *      Author: ACER
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

/* define peripherals base address */
#define GPIOB_BASE_ADDR 0x40020400
#define I2C1_BASE_ADDR 0x40005400

/* configure LCD back-light */
#define BACKLIGHT 0x08
#define NO_BACKLIGHT 0x00

/* starts data */
#define ENABLE 0x04

/* cursor's position */
#define POS 0x80
typedef enum
{
	WRITE, READ
} mode_t;

typedef enum
{
	DATA = 0x01,
	CMD  = 0x00
} type_t;

void LCD_gotoxy(uint8_t row, uint8_t column);
void set_cursor_position(uint8_t cmd);
void LCD_printString(char* str);
void LCD_printChar(uint8_t ch);
void LCD_ClrScr();
void LCD_WriteDATA(uint8_t data);
void LCD_WriteCMD(uint8_t data);
void write_4bits(uint8_t data);
void master_transmit(uint8_t data);
void I2C1_Init();
void LCD_Init();

#endif /* INC_LCD1602_H_ */
