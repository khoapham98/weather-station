#include <Arduino.h>
#include "uart.h"

float data[2] = {0};

void setup()
{
    ESP_UART_Init();
}

void loop()
{
    if (read_sensor(data) == true)
    {
        Serial.print("Humidity: ");
        Serial.println(data[0], 2);
        Serial.print("Temperature: ");
        Serial.println(data[1], 2);
    }
}   