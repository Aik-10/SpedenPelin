//#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

enum GAME_STATE {
  WAITING,
  STARTED,
  WAITING_KEY_PRESS,
  END,
};

volatile unsigned long lastDebounceTime = 0;
volatile unsigned long debounceDelay = 50;

volatile GAME_STATE gameStatus = STARTED;
volatile uint16_t gameScore = 0;

int gameDelayMs = 3000;

int clockPin = 8;  // Connect to CLK pin of SN74HC163N
int clearPin = 7;  // Connect to CLR pin of SN74HC163N
int enablePin = 8; // Connect to ENP/ENT pin of SN74HC163N
int dataPin = A0;   // Connect to Q0 to Q3 outputs of SN74HC163N

void setup() {
  /* This will then shuffle the random function */
  /* randomSeed(analogRead(0));

  initializeLeds();
  initializeButtons(); */

  /* Button interrupts */
  /* for (int i = 0; i < gameButtonPins; ++i) {
    PCMSK2 |= bit(PCINT18 - i);
  }
  PCICR |= bit(PCIE2); */


  /* pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(12, OUTPUT);  */

  Serial.println("Game Inited WAITING");

  Serial.begin(9600);
  /* sei(); */

  /*
    TODO: Initialize here all modules
  */
}

void loop() {
 /*   // Increment count on SN74HC163N
  digitalWrite(clockPin, HIGH);
  delay(1);
  digitalWrite(clockPin, LOW);

  // Read the count
  int count = digitalRead(dataPin);

  // Update LCD display
  lcd.clear();
  lcd.print("Count: ");
  lcd.print(count);

  delay(1000);  */ // Adjust delay as needed

  /* switch (gameStatus) {
    case WAITING:
      //Serial.println("Game status WAITING");
      Serial.println(getRandomNumber());

      delay(100);
      enableAllLeds();
      break;
    case STARTED:
      clearAllLeds();
      delay(100);
      long nextLed = getRandomNumber();
      Serial.println(nextLed);
      setLedState(nextLed, HIGH);
      delay(gameDelayMs);
      break;
    case END:
      Serial.println("Game status END");
      break;
  } */
}

ISR(PCINT2_vect) {
  if ((millis() - lastDebounceTime) < debounceDelay) {
    return;
  }

  if ((digitalRead(PIN2) == LOW)) {
    Serial.println("PIN2 keskeytti");
  }
  if ((digitalRead(PIN3) == LOW)) {
    Serial.println("PIN3 keskeytti");
  }
  if ((digitalRead(PIN4) == LOW)) {
    Serial.println("PIN4 keskeytti");
  }
  if ((digitalRead(PIN5) == LOW)) {
    Serial.println("PIN5 keskeytti");
  }
  if ((digitalRead(PIN6) == LOW)) {
    Serial.println("PIN6 keskeytti");
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
  gameScore = 0;
  gameDelayMs = 3000;
}

void startTheGame() {
  initializeGame();
  gameStatus = STARTED;
  // see requirements for the function from SpedenSpelit.h
}
