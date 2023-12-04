#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>

const int gameButtonPins[] = {PIN2, PIN3, PIN4, PIN5};
const int resetButtonPin = PIN6;

void initializeButtons() {
  for (int i = 0; i < sizeof(gameButtonPins) / sizeof(gameButtonPins[0]); ++i) {
    pinMode(gameButtonPins[i], INPUT_PULLUP);
  }

  pinMode(resetButtonPin, INPUT_PULLUP);
}

#endif