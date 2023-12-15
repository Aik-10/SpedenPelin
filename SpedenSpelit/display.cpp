#include "display.h"

const int LATCH = 10;
const int DATA = 11;
const int CLK = 12;

byte digitOne[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 24 };
byte digitTwo[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 24 };

void initializeDisplay(void) {
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void handleDigitalWrite(byte digits[10], int digit) {
  for (int index = 7; index >= 0; index--) {
    digitalWrite(DATA, (digits[digit] >> index) & 1);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
}

void displayNumber(int number) {
  int digit1 = number / 10;
  int digit2 = number % 10;

  digitalWrite(LATCH, LOW);

  handleDigitalWrite(digitOne, digit1);
  handleDigitalWrite(digitTwo, digit2);

  digitalWrite(LATCH, HIGH);
}

/*
This is right way to display numbers, but teacher want to use `digitalWrite`

void displayNumber(int number) {
  int digit1 = number % 10;
  int digit2 = number / 10;

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[digit1]);
  shiftOut(DATA, CLK, MSBFIRST, ~digitOne[digit2]);
  digitalWrite(LATCH, HIGH);
}

*/
