# AirQualityMonitoring
IoT-based air quality monitoring system using sensors like the laser particle monitor and MQ-135. The system collects real-time data, visualized through an interactive Power BI dashboard to track pollution trends and AQI severity across regions.

🌍 Air Quality Monitoring System with IoT & Power BI 🌍

This project utilizes sensors, including the ZH03 Laser Dust sensor, MQ-135, Arduino, and NodeMCU ESP8266, to monitor air quality in real-time. Data is collected and visualized using Power BI for comprehensive analysis.
📑 Table of Contents

    Introduction
    Features
    Hardware Requirements
    Software Requirements
    Wiring Diagram
    Installation & Setup
    Power BI Dashboard
    License

📖 Introduction

The Air Quality Monitoring System tracks various air quality metrics such as PM1.0, PM2.5, PM10, and gas concentrations (CO2, VOCs) using a combination of sensors. Data is transmitted via Wi-Fi using NodeMCU ESP8266 and visualized on an interactive Power BI dashboard.
✨ Features

    Real-time air quality data collection
    Sensors: ZH03 Laser Dust Sensor, MQ-135 Gas Sensor
    Arduino and NodeMCU ESP8266 integration
    Power BI dashboard for data visualization
    Monitor PM1.0, PM2.5, PM10, and gas concentration levels
    Wi-Fi communication for IoT-enabled data streaming

🔧 Hardware Requirements

    ZH03 Laser Dust Sensor (PM1.0, PM2.5, PM10)
    MQ-135 Gas Sensor
    Arduino (UNO/Nano)
    NodeMCU ESP8266 (for IoT functionality)
    Jumper Wires
    Breadboard
    5V Power Supply

💻 Software Requirements

    Arduino IDE
    ESP8266 Wi-Fi library
    Power BI (for dashboard visualization)
    Power Query (for data transformation)
    NodeMCU drivers

🖼️ Wiring Diagram

[Insert wiring diagram here]
Connections:

    ZH03 Sensor:
        VCC to 5V
        GND to GND
        UART_TX to RX (Arduino)
        UART_RX to TX (Arduino)

    MQ-135 Sensor:
        VCC to 5V
        GND to GND
        A0 to A0 (Arduino Analog Pin)

    NodeMCU ESP8266:
        Connect RX/TX from Arduino to NodeMCU for communication
        Use appropriate pins for I2C communication (D1, D2)

🚀 Installation & Setup

    Clone the repository:

    bash

    git clone https://github.com/a3il/AirQualityMonitoring.git

    Install Arduino libraries:
        Download and install the ESP8266 Wi-Fi library for Arduino from the Library Manager.
        Install sensor-specific libraries (if required).

    Arduino Setup:
        Connect the ZH03 and MQ-135 sensors to the Arduino.
        Upload the provided Arduino sketch to the board.
        Ensure proper baud rate settings for UART communication between sensors and the Arduino.

    NodeMCU Setup:
        Flash the NodeMCU with the provided code for Wi-Fi communication.
        Connect to your Wi-Fi network to enable IoT data transmission.

    Data Streaming:
        Set up a local or cloud-based server to receive data from the NodeMCU.
        Optionally, use MQTT for real-time data streaming.

📊 Power BI Dashboard

To visualize the data:

    Set up Power BI with a connection to your IoT data source.
    Use Power Query to clean and transform incoming data.
    Create visuals to display AQI metrics, including graphs, trends, and maps.
    Customize the dashboard with slicers for easy filtering.

![2023_11_16_20_32_IMG_4455](https://github.com/user-attachments/assets/a72af796-4cbc-40d2-865f-0c9959554bb4)
![2023_11_16_20_32_IMG_4454](https://github.com/user-attachments/assets/984da25f-f31c-437e-b0ae-9588749cae7c)
![2023_11_16_20_32_IMG_4453](https://github.com/user-attachments/assets/edc36ae2-24ff-4f14-ad3b-0d08a4ae6f06)
![2023_11_16_20_32_IMG_4452](https://github.com/user-attachments/assets/de7eb6b6-c88a-4862-a59f-463d5e8a92c0)
![2023_11_16_20_32_IMG_4451](https://github.com/user-attachments/assets/446a0e15-a401-497f-8d74-4d4e78000c87)
![2023_11_16_20_32_IMG_4450](https://github.com/user-attachments/assets/fe120b3d-eae0-4cb3-97d7-f6897d55b183)
![2023_11_16_20_32_IMG_4449](https://github.com/user-attachments/assets/099e2a49-64d5-4d09-864d-4f2848d9627f)
![2023_11_16_20_32_IMG_4448](https://github.com/user-attachments/assets/e0e284aa-b80f-46b0-8aa6-1782970b8512)
![2023_11_16_19_03_IMG_4447](https://github.com/user-attachments/assets/241cb7dc-95e7-4372-8148-894508c7ebb0)
![2023_11_16_18_38_IMG_4445](https://github.com/user-attachments/assets/11740061-5263-46a7-b326-9d5019fcf6dc)
![2023_11_16_18_37_IMG_4444](https://github.com/user-attachments/assets/317df42c-5564-4bc1-9ce3-0c9d64bc1734)
![1725305406503](https://github.com/user-attachments/assets/9f235744-af37-4419-a097-05db69b7a1f2)
![2023_11_16_20_33_IMG_4460](https://github.com/user-attachments/assets/27aa334c-3a9f-4d8f-91a0-0f8e0c4cc4e0)
![2023_11_16_20_33_IMG_4459](https://github.com/user-attachments/assets/7321b5da-08b0-4536-a3f8-eb7389e5072d)
![2023_11_16_20_33_IMG_4458](https://github.com/user-attachments/assets/c1298093-3c1c-4952-a4e7-25b451a8e96f)
![2023_11_16_20_33_IMG_4457](https://github.com/user-attachments/assets/4022fe18-8cba-4ae2-9996-2f55f958fe23)
![2023_11_16_20_33_IMG_4456](https://github.com/user-attachments/assets/327f3600-1753-4c36-bf95-58298823a18b)


📄 License
This project is licensed under the MIT License. See the LICENSE file for details.
