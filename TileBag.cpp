#include <random>

#include "TileBag.h"
#include "LinkedList.h"


TileBag::TileBag(){
    //tileBag = new LinkedList(); // Create a new LinkedList and assign it to the pointer "tileBag"
    //TO DO
}

TileBag::~TileBag(){
    //delete tileBag; // Deletes the LinkedList
    //TO DO
}

void TileBag::createTiles(){
    for(int i = 1; i<=12; i++){ // Loops 12 times
        for(int j = 0; j<4; j++){ // Loops 4 times
            //tileBag->addToTail(i); // Adds a new node with a value of "i" to the LinkedList
            //TO DO
        }
    }
}

int TileBag::generateRandomNum(int min, int max){
    std::random_device device; // Creates a random device
    std::mt19937 engine(device()); // Creates a random engine
    std::uniform_int_distribution<int> dist(min, max); // Creates a random distribution
    int random = dist(engine); // Generates a random number in the distribution
    return random; // Returns the random number
}

void TileBag::shuffle(){
    //TO DO
}

Node* TileBag::pickTile(){
    //TO DO
    return 0;
}