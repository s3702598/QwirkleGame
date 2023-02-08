

#include "Board.h"

Board::Board() {
  x_numberOfTileInThisTurn = INITIAL_STATE;
  x_orientationOfTileInThisTurn = INITIAL_STATE;
}

bool Board::addTileAt(Synchronize &synchronize) {
  bool addSuccess = false;

  //If a new tile is added, there is no condition.
  if (x_synchronize.size() == 0) {
    x_numberOfTileInThisTurn++;
    x_synchronize.push_back(synchronize);
    addSuccess = true;
  } else {
    synchronize.relocateX(getLeftBound());
    synchronize.relocateY(getUpBound());

    //Verify that the synchronise has at least one tile surrounding it and is both empty and empty.
        //TO DO
   }
  return addSuccess;
}

Tile Board::getTileAt(Synchronize synchronize) {
  Tile t = Tile();
  //TO DO
  return t;
}

int Board::getUpBound() {
  int length = MIN_UP;
  for (Synchronize c : x_synchronize) {
    if (c.getY() <= length) {
      length = c.getY() - 1;
    }
  }
  return length;
}

int Board::getDownBound() {
  int length = MIN_DOWN;
  for (Synchronize c : x_synchronize) {
    if (c.getY() >= length) {
      length = c.getY() + 1;
    }
  }
  return length;
}

int Board::getLeftBound() {
  int length = MIN_LEFT;
  for (Synchronize c : x_synchronize) {
    if (c.getX() <= length) {
      length = c.getX() - 1;
    }
  }
  return length;
}

int Board::getRightBound() {
  int length = MIN_RIGHT;
  for (Synchronize c : x_synchronize) {
    if (c.getX() >= length) {
      length = c.getX() + 1;
    }
  }
  return length;
}

std::ostream &operator<<(std::ostream &out, Board &b) {
  //Column index
  out << "  ";
  int colIndex = 0;
  for (int i = b.getLeftBound(); i < b.getRightBound() + 1; ++i) {
    std::string index = std::to_string(colIndex);
    if (colIndex < 10) {
      out << " " << index << " ";
    } else {
      out << " " << index.substr(0, 1) << index.substr(1, 1);
    }
    colIndex++;
  }

  //Dash seperator ---
  out << "\n" << "  -";
  for (int i = b.getLeftBound(); i < b.getRightBound() + 1; ++i) {
    out << "---";
  }

  out << "\n";
  char c = 'A';
  for (int i = b.getUpBound(); i < b.getDownBound() + 1; ++i) {
    std::string s = "";
    s.push_back(c);
    out << c << " |";
    for (int j = b.getLeftBound(); j < b.getRightBound() + 1; ++j) {
      bool has = false;
      for (Synchronize c : b.x_synchronize) {
        if (c.getX() == j && c.getY() == i) {
          out << c.getTile() << "|";
          has = true;
        }
      }
      if (!has) {
        out << "  |";
      }
    }
    out << "\n";
    c++;
  }

  return out;
}

bool Board::hasTileAt(Synchronize synchronize) {
  bool has = false;
  //TO DO
  return has;
}

bool Board::hasUp(Synchronize synchronize) {
  synchronize.relocateY(-1);
  return hasTileAt(synchronize);
}

bool Board::hasDown(Synchronize synchronize) {
  synchronize.relocateY(1);
  return hasTileAt(synchronize);
}

bool Board::hasLeft(Synchronize synchronize) {
  synchronize.relocateX(-1);
  return hasTileAt(synchronize);
}

bool Board::hasRight(Synchronize synchronize) {
  synchronize.relocateX(1);
  return hasTileAt(synchronize);
}

bool Board::isAdd(Synchronize synchronize) {
  return !hasTileAt(synchronize);
      // TO DO
}

int Board::numOfUpTile(Synchronize synchronize) {
  int num = 0;
  // TO DO
  return num;
}

int Board::numOfDownTile(Synchronize synchronize) {
  int num = 0;
  //TO DO
  return num;
}

int Board::numOfLeftTile(Synchronize synchronize) {
  int num = 0;
  //TO DO
  return num;
}

int Board::numOfRightTile(Synchronize synchronize) {
  int num = 0;
  //TO DO
  return num;
}

int Board::noOfCols(Synchronize synchronize) {
  
  return 0;
}

int Board::noOfRows(Synchronize synchronize) {
  
  return 0;
}

int Board::rowPoint(Synchronize synchronize) {
  int rowPoint = 0;
    //TO DO  

  return rowPoint;
}

int Board::colPoint(Synchronize synchronize) {
   int colPoint = 0;
  //TO DO

  return colPoint;
}

int Board::getAddOrient() {
  //TO DO
  return 0;
}

int Board::pinPlayerOneTile() {
  //TO DO
  return 0;
}

int Board::pinPlayerHorizontalTiles() {
  //TO DO
  return 0;
}

int Board::pinPlayerVerticalTiles() {
  //TO DO
  return 0;
}

int Board::totalPoint() {
  int point = 0;
  //TO DO
  return point;
}

void Board::resetValidation() {
  //TO DO
}



std::vector<Tile> Board::columnLn() {
  std::vector<Tile> line;
  //TO DO
  return line;
}

std::vector<Tile> Board::rowLn() {
  std::vector<Tile> line;
  //TO DO
  return line;
}

bool Board::verifyByLine(std::vector<Tile> line) {
  //TO DO

//brute force strategy
  
  return 0;
}

bool Board::isValidForOneSynchronizeCondition() {
  return verifyByLine(rowLn()) && verifyByLine(columnLn());
  
}

bool Board::validateHorizontalAdd() {
  bool isValid = false;
  //TO DO
  return isValid;
}

bool Board::validateVerticalAdd() {
  bool isValid = false;
  //TO DO
  return isValid;
}
bool Board::validateSecondTileCondition() {
  bool isValid = false;
  //TO DO
  return isValid;
}

bool Board::validateMoreThanTwoTileCondition() {
  bool isValid = false;
  //TO DO
  return isValid;
}


bool Board::isValsidForMultiplePlaceCondition() {
  bool isValid = false;
  //TO DO
  return isValid;
}
