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

	CAN.setMode(MCP_LISTENONLY);

	Serial.print("BOOT,");
	Serial.print(millis());
}

void loop() {
	if (CAN_MSGAVAIL == CAN.checkReceive()) {
		unsigned char len = 0;
		unsigned char data[8] = {0};

		if (CAN.readMsgBuf(&len, data) == CAN_OK) {
			unsigned long id = CAN.getCanId();
			bool extended = CAN.isExtendedFrame();
			bool remote = CAN.isRemoteRequest();

			//seq,time_ms,id_hex,flags,dlc,data_hex
			Serial.print(sequenceNumber++);
			Serial.print(',');
			Serial.print(millis());
			Serial.print(',');
			Serial.print(id, HEX);
			Serial.print(',');
			Serial.print(extended ? 1 : 0);
			Serial.print(remote ? 1 : 0);
			Serial.print(',');
			Serial.print(len);

			for (byte i = 0; i < len && i < 8; i++) {
				Serial.print(',');
				if (data[i] < 17) {
					Serial.print('0x');
					Serial.print(data[i], HEX);
				}
			}

			Serial.println();
		}
	}

	if (millis() - lastStatus >= 1000) {
		lastStatus = millis();
	}
}
