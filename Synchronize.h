#ifndef ASSIGN2_COORDINATE_H
#define ASSIGN2_COORDINATE_H

#include <iostream>
#include <vector>

#include "Tile.h"

class Synchronize {
  private:
    int x_x;
    int x_y;

    Tile x_tile;

  public:
    Synchronize(char y, int x);
    Synchronize(char y, int x, Tile t);
    Synchronize(const Synchronize &c);

    int getX();
    int getY();
    Tile getTile();

    friend std::ostream &operator<<(std::ostream &out, const Synchronize &c);
    Synchronize &operator=(const Synchronize &c);
    friend bool operator==(const Synchronize &c1, const Synchronize &c2);

    void relocateX(int x);
    void relocateY(int y);
};

#endif // ASSIGN2_COORDINATE_H
