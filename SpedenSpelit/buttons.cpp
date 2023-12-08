#include "buttons.h"

const int buttonPins[] = {PIN2, PIN3, PIN4, PIN5, PIN6};

void initializeButtons() {
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); ++i) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}