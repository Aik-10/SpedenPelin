#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

/*
  initializeLeds(void) set led port pinMode to OUTPUT
*/
void initializeLeds(void);

/* 
  setLed(byte ledNumber, uint8_t state = HIGH), Handling led state change
 */
void setLed(byte ledNumber, uint8_t state = HIGH);

/*
  clearAllLeds(void) subroutine clears all leds
*/
void clearAllLeds(void);

/*
  setAllLeds subroutine sets all leds
*/
void setAllLeds(void);
#endif