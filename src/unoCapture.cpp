#include <SPI.h>
#include <mcp_scan.h>

/*---------------------------------------*/

const byte CAN_CS = 9;
const unsigned long SERIAL_BAUD = 500000;

MCP_CAN CAN(CAN_CS);
uint32_t sequenceNumber = 0;
uint32_t lastStatus = 0;

void setup() {
	Serial.begin(SERIAL.BAUD);

	while (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) != CAN_OK) {
		delay(500);
	}

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
				if (data[i] < 16) {
					Serial.print('0');
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
