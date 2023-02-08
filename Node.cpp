#include "Node.h"

Node::Node(Tile* tile, Node* next) {
  //deep tile copy now
  this->tile = new Tile(tile->getColour(), tile->getShape());
  this->next = next;
}

Node::~Node() {
  delete tile;
}

Node::Node(Node& other) {
  //This is used to implement a DEEP COPY. 
  this->tile = new Tile(*(other.tile));
  this->next = other.next;
}
