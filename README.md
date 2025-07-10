# Weather Station

## Overview
This project implements a simple weather station using an STM32F411 microcontroller and an ESP8266 microcontroller. The system reads temperature and humidity data from a DHT11 sensor, displays it on an I2C LCD1602, and then sends the same data via UART to an ESP8266. The ESP8266 connects to a Wi-Fi network and hosts a local web page (using Flask) to display real-time sensor readings.

## Demo Video
[Watch demo video on YouTube](https://youtube.com/shorts/CIl2exy2Sw8)

## Features
- Read temperature and humidity from DHT11
- Display values on LCD1602 via I2C
- Transmit sensor data over UART to ESP8266
- ESP8266 hosts a local web server using Flask
- View live data on a web browser within the same Wi-Fi network

## Hardware Components

| Component          | Quantity | Description                         |
| ------------------ | -------- | ----------------------------------- |
| STM32F411          | 1        | Microcontroller Unit                |
| ESP8266 NodeMCU    | 1        | Microcontroller Unit                |
| DHT11              | 1        | Temperature and humidity sensor     |
| LCD1602 with I2C module| 1    | Text display                        |
| Connecting Wires   | 9        | Jumper cables                       |

## Wiring Overview
1. **DHT11**
    - VCC → 3 V
    - GND → GND
    - DATA → PC14 (GPIO)

2. **LCD1602 (I2C)**
    - VCC → 5 V
    - GND → GND
    - SDA → PB9 (I2C1_SDA)
    - SCL → PB8 (I2C1_SCL)

3. **UART to ESP8266**
    - STM32 TX (PB6) → ESP8266 RX
    - GND common between STM32 and ESP8266

> **Note**: Ensure common ground between all devices.