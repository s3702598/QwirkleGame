
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile(Colour colour, Shape shape);
   ~Tile();
   Colour getColour();
   Shape getShape();
   void setColour(Colour colour);
   void setShape(Shape shape);
   std::string tileToString();
   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
