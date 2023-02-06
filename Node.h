
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next); // constructor
   Node(Node& other); // copy constructor
   ~Node(); // destructor
   Tile* getTile();
   Node* getNext();
   void setNext(Node* n);
private:
   Node* next;
   Tile* tile;
};

#endif // ASSIGN2_NODE_H
