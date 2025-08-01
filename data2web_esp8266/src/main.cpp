#include <Arduino.h>
#include "uart_esp.h"
#include "wifi_esp.h"

float data[2] = {0};
void setup()
{
    ESP_UART_Init();
    WiFi_connect(WIFI_SSID, WIFI_PASSWORD);
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
    WiFi_sendData(data);
    delay(1500);
}   
