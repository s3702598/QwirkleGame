#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include <iostream>
#include <string>

class Player {
  private:
    int id;
    std::string name;
    int score;
    LinkedList* hand;
  
  public:
    Player(int id, std::string name);
    Player(int id, std::string name, LinkedList* newHand);
    Player(std::string name);
    ~Player();

    int getPlayerId();
    std::string getPlayerName();
    int getPlayerScore();
    LinkedList* getPlayerHand();

    void setPlayerId(int id);
    void setPlayerName(std::string name);
    void setPlayerScore(int score);
    void setUpPlayerScore(int score);

    void displayTileInHand();
    void clearPlayerHand(); 
};

#endif //PLAYER_H
