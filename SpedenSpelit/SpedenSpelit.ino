//#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

enum GAME_STATE {
  WAITING,
  STARTED,
  END,
};

volatile unsigned long lastDebounceTime = 0;
volatile unsigned long debounceDelay = 50;
volatile unsigned long lastPressedButton = 0;
volatile unsigned long currentLed = lastRandomNumber;
volatile int gameScore = 0;

volatile GAME_STATE gameStatus = WAITING;

int gameDelayMs = 3000;

void setup() {
  /* This will then shuffle the random function */
  randomSeed(analogRead(0));

  initializeLeds();
  initializeButtons();

  /* Button interrupts */
  for (int i = 0; i < gameButtonPins; ++i) {
    PCMSK2 |= bit(PCINT18 - i);
  }
  PCICR |= bit(PCIE2);

  Serial.begin(9600);
  sei();

  /*
    TODO: Initialize here all modules
  */
}

void loop() {
switch (gameStatus) {
    case WAITING:
      if (lastPressedButton >= 4) {
        lastPressedButton = 0;
        startTheGame();
        delay(1000);
        break;
      }
      enableAllLeds();
      break;
    case STARTED:
      clearAllLeds();
      lastPressedButton = 0;
      currentLed = getRandomNumber();
      setLedState(currentLed, HIGH);
      while (lastPressedButton == 0) {
        delay(100);
      }

      if ( lastPressedButton == currentLed ) {
        Serial.println("Oikein");
        gameScore++;
      } else {
        Serial.println("Vituilleen");
        gameStatus = END;
      }

      break;
    case END:
      delay(100);
      Serial.println("aksdkasd");
      enableAllLeds();
      break;
  }
}

volatile unsigned long lastDebounceTime2 = 0;
volatile unsigned long lastDebounceTime3 = 0;
volatile unsigned long lastDebounceTime4 = 0;
volatile unsigned long lastDebounceTime5 = 0;
volatile unsigned long lastDebounceTime6 = 0;

ISR(PCINT2_vect) {
  debounceButton(PIN2, lastDebounceTime2);
  debounceButton(PIN3, lastDebounceTime3);
  debounceButton(PIN4, lastDebounceTime4);
  debounceButton(PIN5, lastDebounceTime5);
  debounceButton(PIN6, lastDebounceTime6);
}

void debounceButton(int pin, volatile unsigned long &lastDebounceTime) {
   unsigned long currentTime = millis();

  if ((currentTime - lastDebounceTime) < debounceDelay) {
    return;
  }

  if ((digitalRead(pin) == LOW)) {
    Serial.print("PIN ");
    Serial.print(pin);
    Serial.println(" keskeytti");

    lastPressedButton = ( pin - 2 );
  }

  lastDebounceTime = millis();
}


ISR(TIMER1_COMPA_vect) {
}

void initializeTimer(void) {
  // see requirements for the function from SpedenSpelit.h
}

void checkGame(byte nbrOfButtonPush) {
  // see requirements for the function from SpedenSpelit.h
}


void initializeGame() {
  gameStatus = WAITING;
  lastPressedButton = 0;
  gameScore = 0;
  currentLed = -1;
  gameDelayMs = 3000;
}

void startTheGame() {
  initializeGame();
  gameStatus = STARTED;
  // see requirements for the function from SpedenSpelit.h
}
