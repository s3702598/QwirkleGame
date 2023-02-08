#include "TileBag.h"
#include "LinkedList.h"


TileBag::TileBag(){
    tileBag = new LinkedList(); // Create a new LinkedList and assign it to the pointer "tileBag"
}

TileBag::~TileBag(){
    delete tileBag; // Deletes the LinkedList
}

void TileBag::createTiles(){
    for(int i = 1; i<=12; i++){ // Loops 12 times
        for(int j = 0; j<4; j++){ // Loops 4 times
            tileBag->addToTail(i); // Adds a new node with a value of "i" to the LinkedList
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
    Node* current = tileBag->getHead(); // Get the head of the LinkedList
    while(current != nullptr){ // While the current node is not empty
        int random = generateRandomNum(1, tileBag->getLength()); // Generates a random number corresponding to a node in the LinkedList
        Node* randomNode = tileBag->getNodeAt(random); // Gets the node at the random index
        int temp = current->getValue(); // Gets the value at the current node
        current->setValue(randomNode->getValue()); // Sets the current node's value to the random node's value
        randomNode->setValue(temp); // Sets the random node's value to the current node's value
        current = current->getNext(); // Moves to the next node
    }
}

Node* TileBag::pickTile(){
    int random = generateRandomNum(1, tileBag->getLength()); // Generates a random number corresponding to a node in the LinkedList
    Node* randomNode = tileBag->getNodeAt(random); // Gets the node at the random index
    tileBag->removeNodeAt(random); // Removes the node from the LinkedList
    return randomNode; // Returns the node
}