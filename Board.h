#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Tile.h"
#include "TileCodes.h"

class Board
{
public:
    Board();
    Board(int noOfCols, int noOfRows);
    ~Board();

    int getNoOfCols();
    int getNoOfRows();
    int getNoOfTilesPlaced();
    Tile* getTile(int rPos, int cPos);
    bool posWithinBoard(int rPos, int cPos);
    bool posIsEmpty(int rPos, int cPos);
    void placeTile(Tile* tile, int rPos, int cPos);
    std::string boardShape();
    std::string boardState();
    std::string printBoardGrid();
    std::string boardToString();
    std::vector<std::vector<Tile*>> getBoardVect();

private:
    int noOfCols;
    int noOfRows;
    int noOfTilesPlaced;
    // 2D vector of pointers to Tiles to store the Board
    std::vector<std::vector<Tile*>> board;

};

#endif // BOARD_H

