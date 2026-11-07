#include <Arduino.h>
#include <SPIFFS.h>

/*---------------------------------------*/

static const int UART_RX = 16;
static const uint32_t UART_BAUD = 500000;

File logFile;
uint32_t lastFlush = 0;
uint32_t lineCount = 0;

void setup() {
	Serial.begin(115200);
	Serial2.begin(UART_BAUD, SERIAL_8N1, UART_RX, -1);

	if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS initialization failed");
        while (true) delay(1000);
    }

    logFile = SPIFFS.open("/canlog.csv", FILE_APPEND);
    if (!logFile) {
        Serial.println("Could not open log file");
        while (true) delay(1000);
    }

    Serial.println("CAN logger ready");
}

void loop() {
    while (Serial2.available()) {
        String line = Serial2.readStringUntil('\n');
        line.trim();

        if (line.length() == 0) continue;

        /*---remove-boot-marker-from-CSV-frame-log---*/
        if (line.startsWith("BOOT,")) {
            Serial.println(line);
            continue;
        }

        if (logFile) {
            logFile.println(line);
            lineCount++;
        }
    }

    /*---batch-write-frames---*/
    if (millis() - lastFlush >= 1000) {
        lastFlush = millis();

        if (logFile) logFile.flush();

        Serial.print("Records written: ");
        Serial.println(lineCount);
    }
}
