#define ANALOG_PIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(ANALOG_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = (voltage - 0.4) * 100 / (2.0 - 0.4); // This is a rough estimation, you might need to calibrate it.

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Voltage (V): ");
  Serial.println(voltage);
  Serial.print("PPM: ");
  Serial.println(ppm);

  delay(1000); // Delay for 1 second before reading again
}
