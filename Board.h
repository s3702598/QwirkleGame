#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Synchronize.h"

#define MIN_UP -2
#define MIN_DOWN 2
#define MIN_LEFT -2
#define MIN_RIGHT 2

#define INITIAL_STATE 0
#define ONE_TILE_ADD 1
#define TWO_TILES_ADD 2
#define HORIZONTAL_ADD 3
#define VERTICAL_ADD 4
#define INVALID_ADD 5

class Board {
  private:
  
    int x_numberOfTileInThisTurn;
    int x_orientationOfTileInThisTurn;

    std::vector<Synchronize> x_synchronize;

  public:
    Board();
    bool addTileAt(Synchronize &synchronize);

    Tile getTileAt(Synchronize synchronize);

    bool hasTileAt(Synchronize synchronize);
    bool hasUp(Synchronize synchronize);
    bool hasDown(Synchronize synchronize);
    bool hasLeft(Synchronize synchronize);
    bool hasRight(Synchronize synchronize);

    bool isAdd(Synchronize synchronize);

    int numOfUpTile(Synchronize synchronize);
    int numOfDownTile(Synchronize synchronize);
    int numOfLeftTile(Synchronize synchronize);
    int numOfRightTile(Synchronize synchronize);
    
    friend std::ostream &operator<<(std::ostream &out, Board &b);

    bool validateSecondTileCondition();
    bool validateMoreThanTwoTileCondition();
    bool validateHorizontalAdd();
    bool validateVerticalAdd();
    bool isValsidForMultiplePlaceCondition();
    
    int noOfRows(Synchronize synchronize);
    int noOfCols(Synchronize synchronize);

    int getAddOrient();

    int colPoint(Synchronize synchronize);
    int rowPoint(Synchronize synchronize);

    int pinPlayerOneTile();
    int pinPlayerHorizontalTiles();
    int pinPlayerVerticalTiles();

    int totalPoint();
    void resetValidation();
 

    std::vector<Tile> columnLn();
    std::vector<Tile> rowLn();

    bool verifyByLine(std::vector<Tile> line);
    bool isValidForOneSynchronizeCondition();

    int getUpBound();
    int getDownBound();
    int getLeftBound();
    int getRightBound();



};

#endif // BOARD_H
