#include "general.h"
#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

const bool DEBUG = false;
const int debounceDelay = 50;
const int gameDelay = 15624; /* (1khz) = (16*10^6) / (1*1024) - 1 (must be <65536) */
const int MAX_SCORE = 100;

volatile unsigned long lastDebounceTime = 0;
volatile unsigned long currentLed = lastRandomNumber;

volatile GAME_STATE gameStatus = WAITING;
volatile long lastPressedButton = -1;
volatile int gameScore, arraySize = 0;

volatile long lastPressedButtons[MAX_SCORE] = {};
volatile int generatedNumberList[MAX_SCORE] = {};

void setup() {
  cli();

  initializeLeds();
  initializeButtons();
  initializeDisplay();

  initializeTimer();
  displayNumber(0);

  Serial.begin(9600);
  sei();
}

void loop() {
  switch (gameStatus) {
    case WAITING:
      handleWaitingStatus();
      break;
    case END:
      handleEndStatus();
      break;
    case WIN:
      handleWinStatus();
      break;
  }
}

ISR(PCINT2_vect) {
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); ++i) {
    debounceButton(buttonPins[i]);
  }
}

ISR(TIMER1_COMPA_vect) {
  if (arraySize >= MAX_SCORE - 1) {
    clearAllLeds();
    return;
  }

  if (arraySize != 0 && arraySize % 10 == 0) {
    degreaseDelay();
    if (DEBUG) {
      Serial.println("Speed up");
    }
  }

  clearAllLeds();
  currentLed = getRandomNumber();
  generatedNumberList[arraySize] = (int)currentLed;

  arraySize++;

  setLedState(currentLed, HIGH);
}

void degreaseDelay(float degreaseAmount = 0.9) {
  OCR1A = OCR1A * degreaseAmount;
}

void initializeTimer(void) {
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = gameDelay;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 &= ~(1 << OCIE1A);
}

void checkGame() {
  if (gameScore > arraySize) {
    gameStatus = END;
    lastPressedButton = -1;
    return;
  }

  if (gameScore == arraySize) {
    clearAllLeds();
  }

  if (lastPressedButtons[gameScore] == generatedNumberList[gameScore]) {
    if (DEBUG) {
      Serial.println("Right next number");
      Serial.println(generatedNumberList[gameScore]);
      Serial.println(lastPressedButtons[gameScore]);
    }

    gameScore++;
    displayNumber(gameScore);
  } else {
    gameStatus = END;

    if (!DEBUG) return;
    Serial.println("Wrong button press");
    Serial.println(generatedNumberList[gameScore]);
    Serial.println(lastPressedButtons[gameScore]);
  }
}


void initializeGame() {
  /* This will then shuffle the random function */
  randomSeed(analogRead(0));

  gameStatus = WAITING;
  lastPressedButton = -1;
  gameScore = 0;
  arraySize = 0;

  OCR1A = gameDelay;
  TIMSK1 |= (1 << OCIE1A);
  TCNT1 = 0;
  currentLed = -1;
}

void startTheGame() {
  initializeGame();
  gameStatus = STARTED;

  if (!DEBUG) return;

  Serial.println("Game started!");
}

void debounceButton(int pin) {
  unsigned long currentTime = millis();

  if ((currentTime - lastDebounceTime) < debounceDelay) {
    return;
  }

  if ((digitalRead(pin) == LOW)) {
    int buttonNumber = pin - 2;

    if ((buttonNumber == lastPressedButton) && (lastPressedButton < 4)) {
      if (DEBUG) {
        Serial.println("Double input BLOCK");
      }
      return;
    }

    if (DEBUG) {
      Serial.print("PIN ");
      Serial.print(pin);
      Serial.println(" debounceButton");
    }

    lastPressedButton = buttonNumber;

    if (gameStatus == STARTED && lastPressedButton < 4) {
      /* Checks is that score button already pressed. */
      if (lastPressedButtons[gameScore] == 0) {
        lastPressedButtons[gameScore] = lastPressedButton;
      }

      checkGame();
    }
  }

  lastDebounceTime = millis();
}

void handleWaitingStatus() {
  if (lastPressedButton >= 4) {
    startTheGame();
    delay(1000);
  } else {
    enableAllLeds();
  }
}

void handleEndStatus() {
  TIMSK1 &= ~(1 << OCIE1A);
  delay(100);

  if (lastPressedButton >= 4) {
    gameStatus = WAITING;
    delay(1000);
  } else {
    clearAllLeds();
    delay(500);
    enableAllLeds();
  }
}

void handleWinStatus() {
  TIMSK1 &= ~(1 << OCIE1A);
  delay(100);

  if (lastPressedButton != 0) {
    gameStatus = WAITING;
  } else {
    enableAllLeds();
  }
}