#include "leds.h"

const int ledPorts[] = { A2, A3, A4, A5 };

void initializeLeds() {
  for (int i = 0; i < sizeof(ledPorts) / sizeof(ledPorts[0]); ++i) {
    pinMode(ledPorts[i], OUTPUT);
  }
}

void setLed(byte ledNumber, uint8_t state = HIGH) {
  if (ledNumber >= 0 && ledNumber < sizeof(ledPorts) / sizeof(ledPorts[0]) && ledPorts[ledNumber]) {
    digitalWrite(ledPorts[ledNumber], state);
  }
}

void clearAllLeds() {
  for (int i = 0; i < sizeof(ledPorts) / sizeof(ledPorts[0]); ++i) {
    digitalWrite(ledPorts[i], LOW);
  }
}

void setAllLeds() {
  for (int i = 0; i < sizeof(ledPorts) / sizeof(ledPorts[0]); ++i) {
    digitalWrite(ledPorts[i], HIGH);
  }
}