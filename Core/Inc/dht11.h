/*
 * 	File		: dht11.h
 *	Created on	: Jul 1, 2025
 *	Author		: Khoa
 * 	GitHub		: https://github.com/khoapham98
 */
#ifndef INC_DHT11_H_
#define INC_DHT11_H_
#define GPIOC_BASE_ADDR 0x40020800

void DHT11_Init();
void receive_data(uint8_t* data);
char check_sum(uint8_t* data);

#endif /* INC_DHT11_H_ */
