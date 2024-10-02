#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <SD_ZH03B.h>
#include <SoftwareSerial.h>

#define WLAN_SSID       "KittathaMunthiri"
#define WLAN_PASS       "P5rK8JwHb5ltSDX"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CSML"
#define AIO_KEY         

const int NO2_SENSOR_PIN = A0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish no2_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/NO2");
Adafruit_MQTT_Publish dust_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Dust");

SoftwareSerial ZHSerial(4, 5); // RX, TX
SD_ZH03B ZH03B(ZHSerial, SD_ZH03B::SENSOR_ZH03B);

void connect() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  Serial.println("Connecting to Adafruit IO...");
  mqtt.connect();
  while (!mqtt.connected()) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to Adafruit IO!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // Connect to Wi-Fi and Adafruit IO
  connect();
}

void readSensorData() {
  char printbuf1[80];

  if (ZH03B.readData()) {
    Serial.print(ZH03B.getMode() == SD_ZH03B::IU_MODE ? "IU:" : "Q&A:");
    sprintf(printbuf1, "PM1.0, PM2.5, PM10=[%d %d %d]", ZH03B.getPM1_0(), ZH03B.getPM2_5(), ZH03B.getPM10_0());
    Serial.println(printbuf1);

    int dustValue = ZH03B.getPM2_5(); // Assuming you want to use PM2.5 value for dust
    dust_pub.publish(String(dustValue).c_str());
  } else {
    Serial.println("ZH03B Error reading stream or Check Sum Error");
  }
}

void loop() {
  // Read NO2 sensor data
  int no2Value = analogRead(NO2_SENSOR_PIN);
  Serial.print("NO2 Value (raw): ");
  Serial.println(no2Value);

  // You need to calibrate your NO2 sensor to convert raw values to ppm
  // Use the calibration values and formula provided by the sensor datasheet

  // Publish NO2 data to Adafruit IO
  no2_pub.publish(String(no2Value).c_str());

  // Read and publish dust sensor data
  readSensorData();

  delay(5000);  // Adjust the delay as needed
}
