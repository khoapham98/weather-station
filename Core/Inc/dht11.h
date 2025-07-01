/*
 * dht11.h
 *
 *  Created on: Jul 1, 2025
 *      Author: ACER
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_
#define TIMEOUT_MAX 1000
#define GPIOC_BASE_ADDR 0x40020800
void mcu_send_start();
void receive_data(uint8_t* data);
void DHT11_Init();
#endif /* INC_DHT11_H_ */
