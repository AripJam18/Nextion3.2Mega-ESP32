#include "Nextion.h"

// Declare Nextion objects for each gauge and text pair
NexGauge GaugeFL = NexGauge(0, 1, "GaugeFL"); //page 0 id 1 , namanya GuageFL
NexText TxtFL = NexText(0, 6, "TxtFL"); //page 0 id 7 , namanya TxtFL

NexGauge GaugeRL = NexGauge(0, 2, "GaugeRL"); //page 0 id 2 , namanya GaugeRL
NexText TxtRL = NexText(0, 7, "TxtRL"); //page 0 id 10 , namanya TxtFL

NexGauge GaugePLM = NexGauge(0, 3, "GaugePLM"); //page 0 id 3 , namanya GaugePLM
NexText TxtPLM = NexText(0, 8, "TxtPLM");//page 0 id 8 , namanya TxtPLM

NexGauge GaugeFR = NexGauge(0, 4, "GaugeFR"); //page 0 id 4 , namanya GaugeFR
NexText TxtFR = NexText(0, 9, "TxtFR");//page 0 id 9 , namanya TxtFR

NexGauge GaugeRR = NexGauge(0, 5, "GaugeRR");//page 0 id 5 , namanya GaugeRR
NexText TxtRR = NexText(0, 10, "TxtRR");//page 0 id 11 , namanya TxtRR

// Variable to track time for periodic updates
unsigned long previousMillis = 0;
const long interval = 2000; // Update interval in milliseconds (2 seconds)

// Function to update a single gauge and text
void updateGaugeAndText(NexGauge &gauge, NexText &text) {
  // Generate a random value between 0 and 100
  uint32_t randomValue = random(0, 101);

  // Update the gauge
  gauge.setValue(randomValue);

  // Update the text with the same value
  char valueText[10];
  utoa(randomValue, valueText, 10);
  text.setText(valueText);
}

void setup(void) {
  Serial.begin(9600);

  // Initialize Nextion display
  nexInit();

  // Initialize random seed
  randomSeed(analogRead(0));
}

void loop(void) {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if it's time to update
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update all gauges and texts
    updateGaugeAndText(GaugeFL, TxtFL);
    updateGaugeAndText(GaugeRL, TxtRL);
    updateGaugeAndText(GaugePLM, TxtPLM);
    updateGaugeAndText(GaugeFR, TxtFR);
    updateGaugeAndText(GaugeRR, TxtRR);
  }

  // Keep Nextion communication active
  nexLoop(NULL);
}
