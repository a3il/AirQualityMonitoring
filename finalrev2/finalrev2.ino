#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>
#include <Wire.h>

#define WLAN_SSID       "CSMLAir"
#define WLAN_PASS       "12345678"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CSML"
#define AIO_KEY         

const int ANALOG_PIN = A0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish co2_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/CO2");
Adafruit_MQTT_Publish nh3_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/NH3");
Adafruit_MQTT_Publish s_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/S");
Adafruit_MQTT_Publish c6h6_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/C6H6");

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
  int nh3Value = analogRead(ANALOG_PIN); 
  int sValue = analogRead(ANALOG_PIN);  
  int c6h6Value = analogRead(ANALOG_PIN);  

  co2_pub.publish(String(co2Value).c_str());
  nh3_pub.publish(String(nh3Value).c_str());
  s_pub.publish(String(sValue).c_str());
  c6h6_pub.publish(String(c6h6Value).c_str());

  delay(5000);
}
