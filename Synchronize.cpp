#include "Synchronize.h"

#include <string>

Synchronize::Synchronize(char y, int x) {
  x_x = x;
  x_y = y - 65;
}

Synchronize::Synchronize(char y, int x, Tile t) {
  x_x = x;
  x_y = y - 65;
  x_tile = t;
}

Synchronize::Synchronize(const Synchronize &c) {
  x_y = c.x_y;
  x_x = c.x_x;
  x_tile = c.x_tile;
}

int Synchronize::getX() {
  return x_x;
}

int Synchronize::getY() {
  return x_y;
}

Tile Synchronize::getTile() {
  return x_tile;
}

std::ostream &operator<<(std::ostream &out, const Synchronize &c) {
  out << (char) (c.x_y + 65) << c.x_x;
  return out;
}

Synchronize &Synchronize::operator=(const Synchronize &c) {
  x_y = c.x_y;
  x_x = c.x_x;
  x_tile = c.x_tile;
  return *this;
}

bool operator==(const Synchronize &c1, const Synchronize &c2) {
  return c1.x_x == c2.x_x && c1.x_y == c2.x_y;
}

void Synchronize::relocateX(int x) {
  x_x += x;
}

void Synchronize::relocateY(int y) {
  x_y += y;
}
