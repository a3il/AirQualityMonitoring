#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <SoftwareSerial.h>

// Wi-Fi credentials
#define WLAN_SSID       "csmlair"
#define WLAN_PASS       "12345678"

// Adafruit IO credentials
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CSML"
#define AIO_KEY         

const int NO2_SENSOR_PIN = A0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish no2_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gases");
Adafruit_MQTT_Publish dust_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dust");

SoftwareSerial espSerial(3, 1); // RX, TX on ESP8266

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
    Serial.println("Failed to connect to Adafruit IO. Check your credentials or internet connection.");
    Serial.println("Return code from MQTT connect is " + String(ret));
    Serial.println("Retrying in 10 seconds...");
    delay(10000);
  }
  Serial.println("Connected to Adafruit IO!");
}

void sendNO2DataToAdafruit(int no2Value) {
  if (no2_pub.publish(no2Value)) {
    Serial.println("NO2 data published successfully");
  } else {
    Serial.println("Failed to publish NO2 data");
  }
}

void sendDustDataToAdafruit(int dustValue) {
  if (dust_pub.publish(dustValue)) {
    Serial.println("Dust data published successfully");
  } else {
    Serial.println("Failed to publish dust data");
  }
}

void readSensorData() {
  if (espSerial.available()) {
    String receivedData = espSerial.readStringUntil('\n');
    Serial.println("Received from Arduino: " + receivedData);

    int ppmValues[2]; // Assuming two values (NO2 and Dust)
    int i = 0;
    char* token = strtok(const_cast<char*>(receivedData.c_str()), ",");
    while (token != NULL && i < 2) {
      ppmValues[i] = atoi(token);
      token = strtok(NULL, ",");
      i++;
    }

    sendNO2DataToAdafruit(ppmValues[0]);
    sendDustDataToAdafruit(ppmValues[1]);
  } else {
    Serial.println("Error reading data from Arduino");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  connect();
}

void loop() {
  int no2Value = analogRead(NO2_SENSOR_PIN);
  Serial.print("NO2 Value (raw): ");
  Serial.println(no2Value);

  readSensorData();

  Serial.println("Delaying for 5000 milliseconds...");
  delay(5000); // Adjust the delay based on your requirement and Adafruit IO rate limits
}
