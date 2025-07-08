#include <Arduino.h>

uint8_t buf[4] = { 0 };

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.readBytes(buf, 4);
    float humi = buf[0] + (buf[1] / (float) 100);
    float temp = buf[2] + (buf[3] / (float) 100);
}   