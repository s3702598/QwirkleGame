#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList {
  public:

    LinkedList();
    ~LinkedList();

    //When taking a tile out of the tile bag
    void removeFront();

    void removeBack();

    //When first discovered inside LL, delete Tile.
    void deleteTile(Tile* tile);

    //whenever a tile is added to a linkedlist
    void addBack(Tile* tile);

    //player hand add the tile from the tile bag's front row.
    //first tile from the tile bag.
    Tile* getFront();

    //maybe to verify the state of the game
    //i.e: endgame state
    int getSize();

    //After the game is over, we must remove the last tile in one of
    //player's hand
    void clear();

    //when a player requests to replace or place something
    //check first if exist
    bool contains(Tile* tileToBeCompared);

    //whenever a player adds or removes a tile from their hand.
    //that selected tile being removed
    void remove(Tile* tileToBeRemoved);

    // void addFront(int data);
    // int get(int i);

    //method to determine how frequently a certain tile exists
    int tileExist(Tile* tileToBeCompared);

    //to create a function toString() { [native code] }() representation of the display list, use the
    //while presenting the tile in the player's hand, a linkedlist
    std::string displayList();

    //player requests to put or change a tile, we must have
    //that particular tile for verification from the list
    //If yes, input tile can be used after using contain().
    //for validation
    // Tile* getSpecificTile(Tile* tile);

    /*
     LinkedListDesign

  The flow between two LinkedLists (assuming the player does not make a mistake when requesting a tile):
Player requests tile, which is checked to see whether it contains something (bool contains), after which it is placed on the board and taken off the player's hand (void remove)
player draw = add 1 tile from tileBag (addBack) (getFront when creating a node to add)
Delete the selected tile from the tileBag (removeFront)

     constantly check game state(getSize)

     at end game state -> there will be one player still keeping tiles -> clear those tile (void clear)

     */

    /*
     Shuffle Algorithm
   FOR 72 TILES, WHILE LOOP 72 times.
Create a tile using a colour and shape that are randomly chosen from a selection of each (using random generator to generate index in order to randomly select from the two collections)
WHILE the list has two instances of the constructed tile
Make a new random tile.
     END WHILE
     ADD the tile to the list
     END WHILE

     */

    Node* head;
    Node* tail;
    int size;
};

#endif // ASSIGN2_LINKEDLIST_H
