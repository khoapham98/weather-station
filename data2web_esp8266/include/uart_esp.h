#pragma once

#define START_BYTE 0xAA
#define STOP_BYTE 0xFF

bool read_sensor(float* data);
void ESP_UART_Init();