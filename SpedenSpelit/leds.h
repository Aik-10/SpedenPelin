#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

/* 
  List and index of every led to game using
*/
const int ledPorts[] = { A2, A3, A4, A5 };

/*
  initializeLeds() subroutine intializes analog pins A2,A3,A4,A5
  to be used as outputs. Speden Spelit leds are connected to those
  pins.  
*/
void initializeLeds() {
  for (int i = 0; i < sizeof(ledPorts) / sizeof(ledPorts[0]); ++i) {
    pinMode(ledPorts[i], OUTPUT);
  }
}

/*
  This function handling ledState changing
*/
void setLedState(int ledNumber, uint8_t state) {
  if (ledNumber >= 0 && ledNumber < sizeof(ledPorts) / sizeof(ledPorts[0])) {
    digitalWrite(ledPorts[ledNumber], state);
  }
}

/*
  clearAllLeds(void) subroutine clears all leds
*/
void clearAllLeds(void) {
  for (int i = 0; i < sizeof(ledPorts) / sizeof(ledPorts[0]); ++i) {
    digitalWrite(ledPorts[i], LOW);
  }
}
/*
  setAllLeds subroutine sets all leds
*/
void enableAllLeds(void) {
  for (int i = 0; i < sizeof(ledPorts) / sizeof(ledPorts[0]); ++i) {
    digitalWrite(ledPorts[i], HIGH);
  }
}

#endif