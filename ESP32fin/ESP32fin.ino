#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <HardwareSerial.h>

// Wi-Fi credentials
#define WLAN_SSID       "csmlair"
#define WLAN_PASS       "12345678"

// Adafruit IO credentials
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CSML"
#define AIO_KEY         

HardwareSerial espSerial(2); // Connect ESP32's RX2 to pin 16, and TX2 to pin 17

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dust");

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600, SERIAL_8N1, 16, 17); // Begin HardwareSerial communication with Arduino
  connect();
}

void connect() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  Serial.println("Connecting to Adafruit IO...");
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println("Retrying in 10 seconds...");
    delay(10000);
  }
  Serial.println("Connected to Adafruit IO!");
}

void loop() {
  if (espSerial.available() > 0) {
    String receivedData = espSerial.readStringUntil('\n');

    // Publish the received data directly to Adafruit IO without printing locally
    feed.publish(receivedData.c_str());

    // Add a delay to prevent rapid publishing
    delay(5000);
  }
}
