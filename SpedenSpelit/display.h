#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>

void initializeDisplay(void);

/* 
  displayNumber(int number), Display number.
*/
void displayNumber(int number);
void handleDigitalWrite(byte digits[10], int digit);
#endif
