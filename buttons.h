#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>

const int gameButtonPins[] = {PIN2, PIN3, PIN4, PIN5};
const int resetButtonPin = PIN6;

/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 2,3,4,5
  2) Initializes 1 button pin for starting the game = Aruino pin 6
  3) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 2,3,4,5,6 is connected to LOW state
*/
void initButtonsAndButtonInterrupts(void);

void initializeButtons() {
  for (int i = 0; i < sizeof(gameButtonPins) / sizeof(gameButtonPins[0]); ++i) {
    pinMode(gameButtonPins[i], INPUT_PULLUP);
  }

  pinMode(resetButtonPin, INPUT_PULLUP);
}

#endif