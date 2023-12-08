#include "display.h"

const int LATCH = 10;
const int DATA = 11;
const int CLK = 12;

const byte digitOne[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 24 };
const byte digitTwo[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 24 };

void initializeDisplay(void) {
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void displayNumber(int number) {
  int digit1 = number % 10;
  int digit2 = number / 10;

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[digit1]);
  shiftOut(DATA, CLK, MSBFIRST, ~digitOne[digit2]);
  digitalWrite(LATCH, HIGH);
}