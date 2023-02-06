#include "TileBag.h"


// constructor
TileBag::TileBag(){
    tileBag = new LinkedList();
    createTiles();
    shuffle();
}

// /* throwing error saying variable tile not used--------------------------- */
TileBag::TileBag(std::vector<std::string> vector)
{
    tileBag = new LinkedList();
    for(unsigned int i = 0; i < vector.size(); i++) //plit string at comma
    {    
        // create new tile using char[0] as colour and char[1] as shape
        int shape = int(vector.at(i)[1]);
        Tile* tile = new Tile(vector.at(i)[0], shape); 
        tileBag->addBack(tile); 
    }
}

// destructor
TileBag::~TileBag()
{
    delete tileBag;
}

// getter for length of TileBag
int TileBag::getLength()
{
    return tileBag->getLength();
}

// // function to create 2 tiles of each combination
void TileBag::createTiles()
{
    int round = 0;
    // we will be iterating twice
    while (round < 2)
    {
        // there are 6 colors and 6 numbers
        for(int i = 0; i < 6 ; ++i)
        {
            Tile* tile1 = new Tile(RED,i+1);
            tileBag->addBack(tile1);

            Tile* tile2 = new Tile(ORANGE,i+1);
            tileBag->addBack(tile2);

            Tile* tile3 = new Tile(YELLOW,i+1);
            tileBag->addBack(tile3);

            Tile* tile4 = new Tile(GREEN,i+1);
            tileBag->addBack(tile4);

            Tile* tile5 = new Tile(BLUE,i+1);
            tileBag->addBack(tile5);

            Tile* tile6 = new Tile(PURPLE,i+1);
            tileBag->addBack(tile6);
        }
        round++;
    }
}

//draws the first tile from the tilebag
Tile* TileBag::drawTile()
{
	char color = tileBag->getTile(0)->getColour();
	int shape = tileBag->getTile(0)->getShape();
	Tile* tile = new Tile(color, shape);
	tileBag->removeFront();
	return tile;
}

void TileBag::addTile(char colour, int shape)
{
	Tile* tile = new Tile(colour,shape);
	tileBag->addBack(tile);
}

void TileBag::addTile(Tile* tile)
{
	tileBag->addBack(tile);
}


// function shuffling tiles in the linked list
void TileBag::shuffle()
{
    int randomNum = 0;
    //iterating through all tiles
    for (int i = 0; i < tileBag->getLength() ; ++i){

        randomNum = generateRandomNum(0, tileBag->getLength()-1);
        // if first element to tile bag, move to back and shift index
        if (randomNum == 0)
            {
            tileBag->addBack(tileBag->getTile(randomNum));
            tileBag->removeFront();
        }
        // if not first element, add to bag and delete at current location
        else
        {
            tileBag->addBack(tileBag->getTile(randomNum));
            tileBag->deleteAtIndex(randomNum);
        }
    }
}
    
Node* TileBag::updateBoard()
{
    Node* drawn = tileBag->findNode(0);
    tileBag->removeFront();
    return drawn;
}

// function to generate random numbers to assist in shuffling the tile bag
int TileBag::generateRandomNum(int min, int max)
{
    std::random_device engine;
	std::uniform_int_distribution<int> uniformIntDist(min, max);

    int randomNum = 0;
    for (int i = 0; i != max; ++i)
    {
        randomNum = uniformIntDist(engine);
    }
    return randomNum;
}

std::string TileBag::bagToString()
{
    std::string bagStr = "";
    int size = tileBag->getLength();
    if (size == 0)
    {
        std::cout << "Bag is empty" << std::endl;
    }
    else
    {
        for (int i = 0; i<size; i++)
        {
            char color = tileBag->getTile(i)->getColour();
            int shape = tileBag->getTile(i)->getShape();
            bagStr.append(color + std::to_string(shape) + ",");
        }
    }
    return bagStr;
}