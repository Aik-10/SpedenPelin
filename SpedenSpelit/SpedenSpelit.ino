#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

const bool DEBUG = true;

const int MAX_SCORE = 100;
enum GAME_STATE { WAITING,
                  STARTED,
                  END,
                  WIN };
volatile unsigned long lastDebounceTime2, lastDebounceTime3, lastDebounceTime4, lastDebounceTime5, lastDebounceTime6 = 0;
volatile unsigned long currentLed = lastRandomNumber;
volatile long lastPressedButton = 0;
volatile long lastPressedButtons[MAX_SCORE] = {};
volatile unsigned long debounceDelay = 150;
volatile GAME_STATE gameStatus = WAITING;
volatile int generatedNumberList[MAX_SCORE] = {};
volatile int gameScore = 0;
volatile int gameDelay = 15624; /* 1khz */
volatile int arraySize = 0;

void setup() {
  cli();

  initializeLeds();
  initializeButtons();
  initializeDisplay();

  /* Button interrupts */
  for (int i = 0; i < gameButtonPins; ++i) {
    PCMSK2 |= bit(PCINT18 - i);
  }
  PCICR |= bit(PCIE2);

  initializeTimer();
  displayNumber(0);


  Serial.begin(9600);
  sei();
}

void loop() {
  switch (gameStatus) {
    case WAITING:
      if (lastPressedButton >= 4) {
        startTheGame();
        delay(1000);
        break;
      }

      
      enableAllLeds();
      break;
    case END:
      TIMSK1 &= ~(1 << OCIE1A);
      delay(100);

      if (lastPressedButton >= 4) {
        gameStatus = WAITING;
        delay(1000);
        break;
      }

      clearAllLeds();
      delay(500);
      enableAllLeds();
      break;
    case WIN:
      TIMSK1 &= ~(1 << OCIE1A);
      delay(100);

      if (lastPressedButton != 0) {
        gameStatus = WAITING;
      }

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

void degreaseDelay(float degreaseAmount = 0.9) {
  OCR1A = OCR1A * degreaseAmount;
}

ISR(TIMER1_COMPA_vect) {
  Serial.println(gameScore);
  if (arraySize >= MAX_SCORE) {
    clearAllLeds();
    return;
  }

  if (arraySize != 0 && arraySize % 10 == 0) {
    degreaseDelay();
    if ( DEBUG ) {
      Serial.println("Speed up");
    }
  }

  clearAllLeds();
  currentLed = getRandomNumber();
  generatedNumberList[arraySize] = (int)currentLed;

  arraySize++;

  setLedState(currentLed, HIGH);
}

void initializeTimer() {
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

  clearAllLeds();

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

void debounceButton(int pin, volatile unsigned long &lastDebounceTime) {
  unsigned long currentTime = millis();

  if ((currentTime - lastDebounceTime) < debounceDelay) {
    return;
  }

  if ((digitalRead(pin) == LOW)) {
    if (DEBUG) {
      Serial.print("PIN ");
      Serial.print(pin);
      Serial.println(" keskeytti");
    }

    lastPressedButton = (pin - 2);

    if (gameStatus == STARTED && lastPressedButton < 4) {
      if (lastPressedButtons[gameScore] == 0) {
        lastPressedButtons[gameScore] = (int)lastPressedButton;
      }

      checkGame();
    }
  }

  lastDebounceTime = millis();
}

void initializeGame() {
  /* This will then shuffle the random function */
  randomSeed(analogRead(0));

  gameStatus = WAITING;
  lastPressedButton = -1;
  gameScore = 0;
  arraySize = 0;

  /* lastPressedButtons[] = {};
  generatedNumberList[] = {}; */

  OCR1A = gameDelay;
  TIMSK1 |= (1 << OCIE1A);
  TCNT1 = 0;
  currentLed = -1;
}

void startTheGame() {

  initializeGame();
  gameStatus = STARTED;

  if (DEBUG) return;

  Serial.println("Game started!");
}
