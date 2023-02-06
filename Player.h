#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "Hand.h"
#include "Board.h"

class Player 
{

public:
    Player(std::string name, TileBag* tileBag, int score);
    Player(std::string name, TileBag* tileBag);
    Player(std::string name, LinkedList* hand, int score);
    ~Player();
    std::string getName();
    int getScore();
    void setName(std::string newName);
    void setScore(int score);
    Hand* getHand();
    void setHand(Hand* hand);
    bool validateName();
    bool checkIfTileInHand(int color, int shape);
    std::string handToString();

    void fillHand(TileBag * tilebag);
    void printHand();
    LinkedList* getHandLL();
    void replaceTile(char colour, int shape, TileBag* tileBag);
    void fillPlayerhandFromFile(std::vector<std::string> vector);




private:
    std::string name;
    int score;
    Hand* hand;
    LinkedList* handLL;
    std::string playerHandString;
    int tilesInHand;

};

#endif //PLAYER_H


