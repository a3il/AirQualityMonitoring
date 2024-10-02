#include <SD_ZH03B.h>

SD_ZH03B ZH03B(Serial, SD_ZH03B::SENSOR_ZH03B);

unsigned long previousMillis = 0;
const long interval = 5000;  // Interval in milliseconds

void setup() {
    Serial.begin(9600);
    delay(1000);

    ZH03B.setMode(SD_ZH03B::IU_MODE);
    Serial.println("-- Initializing ZH03B --");
    delay(200);
}

void readSensorData() {
    char printbuf1[80];

    if (ZH03B.readData()) {
        Serial.print(ZH03B.getMode() == SD_ZH03B::IU_MODE ? "IU:" : "Q&A:");
        sprintf(printbuf1, "PM1.0, PM2.5, PM10=[%d %d %d]", ZH03B.getPM1_0(), ZH03B.getPM2_5(), ZH03B.getPM10_0());
        Serial.println(printbuf1);
    } else {
        Serial.println("ZH03B Error reading stream or Check Sum Error");
    }
}

void loop() {
    unsigned long currentMillis = millis();

    Serial.println("Normal default IU Mode. Reading every 5 sec");
    if (currentMillis - previousMillis >= interval) {
        readSensorData();
        previousMillis = currentMillis;
    }

    Serial.println("Go to Sleep");
    if (ZH03B.sleep()) Serial.println("Sleep mode confirmed");

    Serial.println("Sleep mode, should return errors");
    if (currentMillis - previousMillis >= interval) {
        readSensorData();
        previousMillis = currentMillis;
    }

    Serial.println("Wake up");
    if (ZH03B.wakeup()) Serial.println("Woke up successfully");

    Serial.println("Set Q&A mode, readings every 5 sec");
    ZH03B.setMode(SD_ZH03B::QA_MODE);
    delay(100);

    if (currentMillis - previousMillis >= interval) {
        readSensorData();
        previousMillis = currentMillis;
    }

    Serial.println("Go to Sleep");
    if (ZH03B.sleep()) Serial.println("Sleep mode confirmed");

    Serial.println("Sleep mode, should return errors");
    if (currentMillis - previousMillis >= interval) {
        readSensorData();
        previousMillis = currentMillis;
    }

    Serial.println("Wake up");
    if (ZH03B.wakeup()) Serial.println("Woke up successfully");

    Serial.println("Set IU mode, readings every 5 sec");
    ZH03B.setInitiativeMode();
    delay(200);
}
