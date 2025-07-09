#include <Arduino.h>
#include "uart_esp.h"
#include "wifi_esp.h"

float data[2] = {0};

void setup()
{
    ESP_UART_Init();
    WiFi_connect(REDACTED_SSID, REDACTED_PASS);
}

void loop()
{
    // if (read_sensor(data) == true)
    // {
    //     Serial.print("Humidity: ");
    //     Serial.println(data[0], 2);
    //     Serial.print("Temperature: ");
    //     Serial.println(data[1], 2);
    // }
    delay(2000);
    Serial.println("Hello World");
}   