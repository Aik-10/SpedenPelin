#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"


void setup()
{
  /*
    Initialize here all modules
  */
}

void loop()
{
  /*
    This loop function constantly checks if
	player has pushed a button and there is
	need for checking the game status
  */
}

ISR(PCINT2_vect) {
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
}


ISR(TIMER1_COMPA_vect)
{
  /*
    Here you generate a random number that is used to
	set certain led.
	
	Each timer interrupt increments "played" numbers,
	and after each 10 numbers you must increment interrupt
	frequency.
	
	Each generated random number must be stored for later
	comparision against player push button presses.
  */
  
}



void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
}

void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h
}

