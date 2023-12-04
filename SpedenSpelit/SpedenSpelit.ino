//#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

enum GAME_STATE {
  WAITING,
  STARTED,
  END,
};

volatile unsigned long lastDebounceTime2 = 0;
volatile unsigned long lastDebounceTime3 = 0;
volatile unsigned long lastDebounceTime4 = 0;
volatile unsigned long lastDebounceTime5 = 0;
volatile unsigned long lastDebounceTime6 = 0;

volatile unsigned long debounceDelay = 50;
volatile unsigned long lastPressedButton = 0;
volatile unsigned long currentLed = lastRandomNumber;
volatile int gameScore = 0;

volatile GAME_STATE gameStatus = WAITING;

int gameDelayMs = 3000;

void setup() {
  cli();
  /* This will then shuffle the random function */
  randomSeed(analogRead(0));

  initializeLeds();
  initializeButtons();

  /* Button interrupts */
  for (int i = 0; i < gameButtonPins; ++i) {
    PCMSK2 |= bit(PCINT18 - i);
  }
  PCICR |= bit(PCIE2);

  initializeTimer();

  Serial.begin(9600);
  sei();

  /*
    TODO: Initialize here all modules
  */
}

/* 

Serial.println(OCR1A);
OCR1A = OCR1A * 0.9;
 */

void loop() {
  switch (gameStatus) {
    case WAITING:
      if (lastPressedButton >= 4) {
        Serial.println(OCR1A);
        OCR1A = OCR1A * 0.9;
        lastPressedButton = 0;
        //startTheGame();
        delay(1000);
        break;
      }
      //enableAllLeds();
      break;
    case STARTED:
      clearAllLeds();
      lastPressedButton = 0;
      currentLed = getRandomNumber();
      setLedState(currentLed, HIGH);
      while (lastPressedButton == 0) {
        delay(100);
      }

      if (lastPressedButton == currentLed) {
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

    lastPressedButton = (pin - 2);
  }

  lastDebounceTime = millis();
}


ISR(TIMER1_COMPA_vect) {
  //if ( gameStatus != STARTED ) return;

  clearAllLeds();
  lastPressedButton = 0;
  currentLed = getRandomNumber();
  setLedState(currentLed, HIGH);

  Serial.println("TIMER1_COMPA_vect");
}

void initializeTimer() {
  TCCR1A = 0;  // set entire TCCR1A register to 0
  TCCR1B = 0;  // same for TCCR1B
  TCNT1 = 0;   //initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;  // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
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
