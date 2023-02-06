#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

Tile::~Tile(){
    // nothing to do here
}

Colour Tile::getColour()
{
    return colour;
}

Shape Tile::getShape()
{
    return shape;
}

void Tile::setColour(Colour colour)
{
    this->colour = colour;
}

void Tile::setShape(Shape shape)
{
    this->shape = shape;
}

std::string Tile::tileToString(){
    std::string tile = colour + std::to_string(shape);
    return tile;
}
