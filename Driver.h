#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include "Player.h"
#include "Board.h"

class Driver
{
    public:
        Driver();
        Driver(std::string player1Name, std::string player2Name);
        Driver(Player* player1, Player* player2, TileBag* tileBag, Board* board, bool player1Turn);
        
        ~Driver();

        bool validatePlacing(Tile* tile, int rPos, int cPos, Board* board);
        bool isOnEmpty(int rPos, int cPos);
        bool isValidPlacing(Tile* tile, int rPos, int cPos);
        bool nearColorOrShape(Tile* tile, int rPos, int cPos, int newRPos, int newCPos);
        bool noDuplicateInLine(Tile* tile, int rPos, int cPos, Board* board);
        void pointsScored(Player* player, Board* board, int rPos, int cPos);
        int calcPtsInRow(int rPos, int cPos, Board* board);
        int calcPtsInCol(int rPos, int cPos, Board* board);
        std::tuple<Player*, Player*, TileBag*, Board*, bool> fileLoad();
        void save();
        void printBoard(Board* board);
        void printBoardGrid(Board* board);
        Player* getPlayer(std::string name);
        TileBag* getTileBag();
        std::vector<std::string> stringToVector(std::string str, std::vector<std::string> vect);
        Board* tilesOnBoard(std::vector<std::string>vect, Board* board);
        int stringToInt(std::string num);
        void fillPlayersHands(TileBag* tileBag);
        void loadHandsFromFile(std::vector<std::string> vector1,std::vector<std::string> vector2);
        LinkedList* handLLFromVector(std::vector<std::string> vector);

    private:
        std::string player1Name;
        std::string player2Name; 

        //Array of 2 players
        Player* player1;
        Player* player2;
        std::array<Player* , 2> players;
        Hand* p1Hand;
        Hand* p2Hand;
        Board* board;
        TileBag* tileBag;
        bool player1Turn;      

};
#endif //DRIVER_H
