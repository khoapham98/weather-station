#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* server_url = "http://192.168.1.9:5000/data";

void WiFi_sendData(float* _data)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        WiFiClient client; 

        http.begin(client, server_url);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        String data = "humi=" + String(_data[0]) + "&temp=" + String(_data[1]);
        int httpResponseCode = http.POST(data);

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        String response = http.getString();
        Serial.println("Server response: " + response);

        http.end();
    }
    else
    {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}

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

