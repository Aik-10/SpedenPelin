#include "general.h"

enum GAME_STATE { WAITING,
                  STARTED,
                  END,
                  WIN };

long lastRandomNumber = -1;  // Initialize to a value not in the desired range

long getRandomNumber() {
  long randomGeneratedNumber;

  do {
    randomGeneratedNumber = random(0, 4);
  } while (randomGeneratedNumber == lastRandomNumber);

  lastRandomNumber = randomGeneratedNumber;
  return randomGeneratedNumber;
}