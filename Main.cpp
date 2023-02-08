#include "LinkedList.h"
#include "Messages.h"
#include <iostream>
#include <array>
#include<random>
#include <stdlib.h>

#define EXIT_SUCCESS    0

/*
 1. To receive a shuffled tile bag every time you play the game, go into playGame() in Driver and uncomment shuffleTileBag() before commenting out method tileBagUnitTest ().
Simply leave the software in its current form to run unit tests.
 */
int main(void) {

  Messages messeges = Messages();
  messeges.executeGame();

  return EXIT_SUCCESS;
}
