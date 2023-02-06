#include "Hand.h"

/* constructor for the hand */
Hand::Hand(TileBag* tilebag)
{
    tiles = new LinkedList();
    for (int i = 0; i < 6; i++)
    {
        tilebag->drawTile();
    }
    numTiles = 6;
}

Hand::Hand(std::vector<std::string> vector)
{
    tiles = new LinkedList();
    for(unsigned int i = 0; i < vector.size(); i++) 
    {    
        // create new tile using char[0] as colour and char[1] as shape
        // convert to linked list structure 
        int shape = charToInt(vector.at(i)[1]);
        Tile* tile = new Tile(vector.at(i)[0], shape); 
        tiles->addBack(tile);
    }
}

/* destructor for the hand */
Hand::~Hand()
{
    delete tiles;
}

/* helper function to extract a single tile from the
tile bag and put in Hand */

void Hand::drawTile(TileBag* tilebag)
{
    while (numTiles != 6)
    {
        tiles->addFront(tilebag->drawTile());
        numTiles++;
    }
}

/* helper function to remove tile from Hand and draw from 
TileBag */
void Hand::replaceTile(char colour, int shape, TileBag* tileBag)
{
    tileBag->addTile(colour, shape);
	drawTile(tileBag);
    
}

/* helper function to print out the player's hand as a string */
std::string Hand::handToString()
{
    std::string handStr = "";
    for (int i = 0; i<6; i++)
        {
            char color = tiles->getTile(i)->getColour();
            int shape = tiles->getTile(i)->getColour();
            handStr.append(color + std::to_string(shape) + ",");
        }
    return handStr;
}

/* getter for the number of tiles in a hand */
int Hand::getSize()
{
    return tiles->getLength();
}

Tile* Hand::inputToTile(std::string tileInput) {

    // determining the tile that is about to be placed by user
    int size = tileInput.size();
    //tile is always represented by two characters.
    char char_array[size + 1];
    strcpy(char_array, tileInput.c_str());

    //Characters are converted to integers using ASCII.
    char colour = char_array[0];
    int shape = char_array[1] - ASCII_FOR_0;

    Tile* tile = new Tile(colour, shape);

    return tile;
}

//tile is positioned second in any command.
std::string Hand::getTileFromUserInput(std::string input) {

    std::string tile = "";

    std::istringstream token(input);

    //tile is positioned second in any command.
    for (int i = 0; i < 1; i++) 
    {
        token >> tile;
    }
    token >> tile;

    return tile;
}

//location is at the fourth place in the placing instruction, thus we loop
//to get to the fourth position, three words must be tokenized.
std::string Hand::getLocationFromUserInput(std::string input) {
    std::string location = "";

    std::istringstream token(input);

    for (int i = 0; i < 3; i++) 
    {
        token >> location;
    }

    token >> location;

    return location;
}

// helper function to check if tile is in hand
bool Hand::isTileInHand(char color, int shape)
{
	return tiles->tileExists(color, shape);
}

LinkedList* Hand::getTiles()
{
    return this->tiles;
}


int Hand::charToInt(char num) 
{
    int n = int(num);
    return n;
}



