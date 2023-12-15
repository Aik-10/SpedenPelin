#include "buttons.h"

void initializeButtons(int buttonPins[]) {
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); ++i) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  PCICR |= B00000100;
  PCMSK2 |= B01111100;
}