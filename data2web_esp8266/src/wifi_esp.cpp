#include <Arduino.h>
#include <ESP8266WiFi.h>

void WiFi_connect(const char* wifi_name, const char* password)
{
    delay(100);
    WiFi.begin(wifi_name, password);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi connected! IP address: ");
    Serial.println(WiFi.localIP());
}