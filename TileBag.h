#ifndef TILEBAG_H
#define TILEBAG_H

#include "Node.h"


class TileBag
{
public:
TileBag();
~TileBag(); // Deletes the LinkedList

void createTiles();
int generateRandomNum(int min, int max);
void shuffle();
Node* pickTile();


private:


};
#endif // BOARD_H
