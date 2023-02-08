#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Board.h"
#include "Player.h"
#include "LinkedList.h"
#include <iostream>
#include <regex>
#include <string>

class Driver {
  public:
    Driver();
    ~Driver();

    void playGame(std::string player1Name, std::string player2Name, int selection);

    void addPlayer(Player *p);
    Player* getTopScorePlayer(int i);
    void addTopPlayer(Player* p);
    Player* getPlayerWithTopScoreWhenEnd();
    void keepTopRecords();

    void setUpTilesInitially(Player *player, LinkedList *tileBag);
    //void shuffleTileBag(LinkedList *tileBag);
    int randomNumberGenerate();

    bool validateFormat(std::string input);

    std::string getTileFromUserInput(std::string input);
    std::string getLocationFromUserInput(std::string input);

    bool validateTileExistInHand(std::string tileInput, Player *player);

    bool validateLegalMove(std::string tileInput, std::string gridLocation,
        std::string inputFromUser, Player *player);

    void printScore();

    void getState(Player *p);

    int countToken(std::string);

    void saveGame(std::string filename, Player* player, LinkedList* tileBag);
    std::string getNameOfFileFromUserInput(std::string input);

    void printMessageWhenSaveGame(std::string& inputFromUser, Player* player,
        LinkedList* tileBag, bool& quitGame);
    void printMessageWhenInvalidFormat(std::string& inputFromUser,
        Player* player, LinkedList* tileBag, bool& quitGame, bool& ableToAdd);
    void printInvalidWhenIllegalMove(bool& ableToAdd, bool& quitGame,
        std::string& inputFromUser);

    void designPlayerState(std::string& firstPlayerName,
        std::string& scoreFirstPlayer, std::string& firstPlayerHand,
        std::string& secondPlayerName, std::string& scoreSecondPlayer,
        std::string& secondPlayerHand);
    LinkedList* designTileBag(std::string& tileBag);
    void forwardTileBag(std::string& tileBagStr);

    void designBoard(std::string& moves);
    void load(std::string& playerTurn, int selection);

    void keepRecords(std::string inputFromUser);
    std::string getRecords();

    void forPlaceMultipleTiles(bool& ableToAddTile,
        bool& firstPlayerTurn, bool& repromptPlayer, bool& quitGame,
        Player* player, LinkedList* tileBag);
    void shuffleTileBag(LinkedList *tileBag);
    void tileBagUnitTest(LinkedList* tileBag);

  private:
    Board board;
    Player *playerList[2];
    int playerCount;
    std::string tileBagStr;
    std::array<Player*, 1> topScoreplayer;

};

#endif //ASSIGN2_ENGINE_H
