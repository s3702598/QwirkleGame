#include <iostream>
#include "Hand.h"



Hand::Hand(TileBag* tilebag)
{
    // Initialize the hand with 6 tiles from the tilebag
    numTiles = 6;
     hand = new LinkedList();
    //TO DO
}

Hand::~Hand()
{
    // Delete the linked list and all of the nodes
    delete hand;
}

void Hand::drawTile(TileBag tilebag)
{
    // Draw a tile from the tilebag and add it to the hand
   //TO DO
    numTiles++;
}

void Hand::placeTile(Board board)
{
    // Place a tile from the hand onto a valid spot on the board
    // This function will depend on what the user input is
   //TO DO
    this->numTiles--;
}

void Hand::replaceTile(TileBag tilebag)
{
    // Remove a tile from the hand and replace it with one from the tilebag
    // This function will depend on what the user input is
    hand->removeFront();
    //TO DO
}

std::string Hand::handToString()
{
    // Return a string representation of the hand
    std::string out = "";
    //TO DO
    return out;
}

int Hand::getSize()
{
    // Return the size of the hand
    return numTiles;
}