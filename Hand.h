#ifndef HAND_H
#define HAND_H

#include <iostream>

#include "TileBag.h"
#include "Board.h"
#include "LinkedList.h"

class Hand
{
public:

    Hand(TileBag* tilebag);
    ~Hand();
    void drawTile(TileBag tilebag);
    void placeTile(Board board);
    void replaceTile(TileBag tilebag);
    std::string handToString();
    int getSize();

private:

    int numTiles;
   LinkedList* hand;
    
    
   

};

#endif // HAND_H