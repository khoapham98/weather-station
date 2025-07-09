#include <Arduino.h>

uint8_t buf[6] = { 0 };

void setup()
{
    Serial.begin(9600, SERIAL_8E1);
    Serial.println("ESP8266 UART Receiver Ready");
}

void loop()
{
    if (Serial.available())
    {   
        uint8_t start = Serial.read();
        if (start == 0xAA)
        {
            uint8_t cnt = Serial.readBytes(&buf[1], 5);
            if (cnt == 5 && buf[5] == 0xFF)
            {
                float humi = buf[1] + (buf[2] / 100.0f);
                float temp = buf[3] + (buf[4] / 100.0f);
                Serial.print("Humidity: ");
                Serial.println(humi, 2);
                Serial.print("Temperature: ");
                Serial.println(temp, 2);
            }
            else
            {
                while (Serial.available()) 
                {
                    Serial.read();
                }
            }
        }
    }
}   