#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>

int LATCH = PIN2;
int DATA = PIN3;
int CLK = PIN4;

byte digitOne[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 24 };
byte digitTwo[10] = { 64, 121, 36, 48, 25, 18, 2, 120, 0, 24 };

void initializeDisplay() {
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

#endif
