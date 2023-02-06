#ifndef HAND_H
#define HAND_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include "TileBag.h"
#include "Board.h"

#define ASCII_FOR_0 48

class Hand 
{
public:
    Hand(TileBag* tilebag);
    Hand(std::vector<std::string> vector);
    ~Hand();
    void drawTile(TileBag* tilebag);
    void replaceTile(char color, int shape, TileBag* tilebag);
    Tile* inputToTile(std::string tileInput);
    std::string getTileFromUserInput(std::string input);
    std::string getLocationFromUserInput(std::string input);
    std::string handToString();
    int getSize();
    int charToInt(char num);
    bool isTileInHand(char color, int shape);
    LinkedList* getTiles();

private:
    int numTiles;
    LinkedList* tiles;

};

#endif // HAND_H