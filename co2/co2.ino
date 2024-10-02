#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Wire.h>

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "KittathaMunthiri"
#define WLAN_PASS       "P5rK8JwHb5ltSDX"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CSML"
#define AIO_KEY         

/************************* MQ-135 Sensor Setup *****************************/

const int ANALOG_PIN = A0;

/************************* Adafruit.io Setup *********************************/

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish co2_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/co2");

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
  delay(10);
  
  connect();
}

void loop() {
  int co2Value = analogRead(ANALOG_PIN);

  Serial.print("CO2 Value: ");
  Serial.println(co2Value);

  co2_pub.publish(co2Value);

  delay(10000); // Delay for 10 seconds before sending the next reading
}
