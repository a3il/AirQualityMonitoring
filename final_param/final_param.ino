#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>
#include <Wire.h>
#define WLAN_SSID       "KittathaMunthiri"
#define WLAN_PASS       "P5rK8JwHb5ltSDX"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CSML"
#define AIO_KEY         "aio_GcaG30uxH9N1Ij3CbUxmPzGCwzLb"
const int ANALOG_PIN = A0;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish parameters_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/parameters");
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


  StaticJsonDocument<200> doc;
  doc["CO2"] = co2Value;
  doc["NH3"] = nh3Value;
  doc["S"] = sValue;
  doc["C6H6"] = c6h6Value;


  char parametersString[200]; 
  serializeJson(doc, parametersString, sizeof(parametersString));

  Serial.println(parametersString); 


  parameters_pub.publish(parametersString);

  delay(5000);
}
