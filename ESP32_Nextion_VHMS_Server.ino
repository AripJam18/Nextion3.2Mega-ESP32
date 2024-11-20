//library yang harus diinstall 
//1. ITEADLIB_Arduino_Nextion
//2. EspSoftwareSerial by Dirk Kaar v8.1.0

#include "Nextion.h"

// Gunakan pin UART sesuai ESP32
#define RXD2 16  // Pin RX (hubungkan kabel kuning(RX) dari Nextion ke Pin ini)
#define TXD2 17  // Pin TX (hubungkan kabel biru(TX) dari Nextion ke Pin ini)
HardwareSerial mySerial(2); // UART2 digunakan untuk Nextion

// Declare Nextion objects
NexGauge GaugeFL = NexGauge(0, 1, "GaugeFL");
NexText TxtFL = NexText(0, 6, "TxtFL");

NexGauge GaugeRL = NexGauge(0, 2, "GaugeRL");
NexText TxtRL = NexText(0, 7, "TxtRL");

NexGauge GaugePLM = NexGauge(0, 3, "GaugePLM");
NexText TxtPLM = NexText(0, 8, "TxtPLM");

NexGauge GaugeFR = NexGauge(0, 4, "GaugeFR");
NexText TxtFR = NexText(0, 9, "TxtFR");

NexGauge GaugeRR = NexGauge(0, 5, "GaugeRR");
NexText TxtRR = NexText(0, 10, "TxtRR");

// Variable to track time for periodic updates
unsigned long previousMillis = 0;
const long interval = 2000; // 2 seconds

void updateGaugeAndText(NexGauge &gauge, NexText &text) {
  uint32_t randomValue = random(0, 101);
  gauge.setValue(randomValue);

  char valueText[10];
  utoa(randomValue, valueText, 10);
  text.setText(valueText);
}

void setup(void) {
  Serial.begin(115200); // Debugging serial
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // Nextion serial
  nexSerial = mySerial; // Assign Nextion serial to library
  nexInit();

  randomSeed(millis());
  Serial.println("Setup complete");
}

void loop(void) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    updateGaugeAndText(GaugeFL, TxtFL);
    updateGaugeAndText(GaugeRL, TxtRL);
    updateGaugeAndText(GaugePLM, TxtPLM);
    updateGaugeAndText(GaugeFR, TxtFR);
    updateGaugeAndText(GaugeRR, TxtRR);
  }

  nexLoop(NULL);
}
