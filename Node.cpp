#include "Node.h"


Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other)
{
   tile = other.tile;
   next = other.next;
}

//destructor
Node::~Node()
{
   // nothing to do here
}

Tile* Node::getTile()
{
   return this->tile;
}

Node* Node::getNext()
{
   return next;
}

void Node::setNext(Node* n)
{
   next = n;
}



