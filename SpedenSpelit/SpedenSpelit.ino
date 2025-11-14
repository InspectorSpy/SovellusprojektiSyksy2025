#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler


void setup()
{
  /*
    Initialize here all modules
  */
  Serial.begin(9600);
  initializeDisplay();
  initializeGame();
  initializeLeds();
  initializeTimer();
  initButtonsAndButtonInterrupts(); // init lisätty
}

void loop()
{
  if(buttonNumber>=0)
  {
     // start the game if buttonNumber == 4
     // check the game if 0<=buttonNumber<4
     buttonNumber = -1; // reset var lisätty
  }

  if(newTimerInterrupt == true)
  {
     // new random number must be generated
     // and corresponding let must be activated
     newTimerInterrupt = false; // reset var lisätty
  }
  else {
    // älä tee mitään, oota keskeytystä: Lisätty
  }
}

void initializeTimer(void)
{
  // see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  newTimerInterrupt = true;
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

