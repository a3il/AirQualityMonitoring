#include <SD_ZH03B.h>
#include <SoftwareSerial.h>

SoftwareSerial ZHSerial(4, 5); // RX, TX
SoftwareSerial espSerial(6, 7); // Connect ESP8266's TX to pin 6, and RX to pin 7

SD_ZH03B ZH03B(ZHSerial, SD_ZH03B::SENSOR_ZH03B);

// Define the analog pin for the NO2 sensor
const int no2SensorPin = A0;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Begin SoftwareSerial communication with ESP8266
  delay(1000);
  ZHSerial.begin(9600);
  delay(100);
  ZH03B.setInitiativeMode(); // IU mode
  delay(200);
}

void sendSensorDataToESP(int pm1, int pm2_5, int pm10, int no2Value) {
  char ppmValues[30];
  sprintf(ppmValues, "%d,%d,%d,%d", pm1, pm2_5, pm10, no2Value);
  espSerial.println(ppmValues); // Send the PPM values as a string to the ESP8266
}

void readSensorData() {
  if (ZH03B.readData()) {
    int pm1 = ZH03B.getPM1_0();
    int pm2_5 = ZH03B.getPM2_5();
    int pm10 = ZH03B.getPM10_0();

    if (pm1 >= 0 && pm2_5 >= 0 && pm10 >= 0) {
      int no2Value = analogRead(no2SensorPin);
      sendSensorDataToESP(pm1, pm2_5, pm10, no2Value);
    }
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    readSensorData();
    delay(1000);
  }
}
