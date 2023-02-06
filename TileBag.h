#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"
#include "Tile.h"
#include <iostream>
#include <random>

class TileBag
{
    public:
        TileBag();
        TileBag(std::vector<std::string> vector);
        ~TileBag();
        void createTiles();
        Tile* drawTile();
        int generateRandomNum(int min, int max);
        void shuffle();
        Node* updateBoard();
        // std::vector<std::string> bagToString();
        std::string bagToString();
        void addTile( char colour, int shape);
        void addTile(Tile* tile);

        //methods from LinkedList
        int getLength();

    private:
        LinkedList* tileBag;
        LinkedList* loadedBag;
        Node* head;

};

#endif //TILEBAG_H
