/*
 * timer.h
 *
 *  Created on: Jul 1, 2025
 *      Author: ACER
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define TIM2_BASE_ADDR 0x40000000
void delay_ms(uint32_t ms);
void delay_us(uint16_t us);
void TIM2_Init();
#endif /* INC_TIMER_H_ */
