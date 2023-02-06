#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Node.h"

class LinkedList
{
public:
    LinkedList();
   ~LinkedList();

   Tile* getTile(int i);
   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void removeFront();
   void removeBack();
   void deleteAtIndex(int i);
   int getLength();
   Node* findNode(int i);
   bool tileExists(char colour, int shape);
   std::vector<std::string> listToString(LinkedList* list);
   Node* getHead();
   void printAll();
   std::string printString();
   // std::string intToString(int num);


private:
   Node* head;
   Node* tail;
   int length;
};


#endif // ASSIGN2_LINKEDLIST_H
