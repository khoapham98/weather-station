#include <Arduino.h>
#include "uart_esp.h"

bool read_sensor(float* data)
{
    if (!Serial.available()) return false;

    uint8_t start = Serial.read();
    if (start != START_BYTE) { return false; }

    uint8_t buf[5] = { 0 };
    uint8_t cnt = Serial.readBytes(buf, 5);

    if (cnt != 5)   
    { 
        while (Serial.available()) { Serial.read(); }
        return false; 
    }
    if (buf[4] != STOP_BYTE) { return false; }

    data[0] = buf[0] + (buf[1] / 100.0f);
    data[1] = buf[2] + (buf[3] / 100.0f);
    return true; 
}

void ESP_UART_Init()
{
    Serial.begin(9600, SERIAL_8E1);
}