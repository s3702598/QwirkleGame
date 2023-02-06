#include "Player.h"

/* constructor for player for new game */
Player::Player(std::string name, TileBag* tileBag, int score)
{
    this->name = name;
    this->score = 0;
    this->hand = new Hand(tileBag);
}

// cnstrcutor utilising hand LinkedList declared in Player
// LinkedList hand in Hand.cpp was causing segmentation faults
Player::Player(std::string name, TileBag* tileBag)
{
    this->name = name;
    this->score = 0;
    this->handLL = new LinkedList();
}

// constructor for loading game
Player::Player(std::string name, LinkedList* hand, int score)
{
	this->name = name;
	this->handLL = hand;
	this->score = score;
}


/* destructor for player */
Player::~Player()
{
    delete hand;
}

/* getter for the player's score */
int Player::getScore()
{
    return score;
}

// methods to give hand functionality in Player:

void Player::printHand()
{
  handLL->listToString(handLL);
}

//fills the hands of the player
void Player::fillHand(TileBag* tileBag)
{
    tilesInHand = 0;
  for (int i = 0; i < 6; i++)
  {
    handLL->addFront(tileBag->drawTile());
    tilesInHand++;
  }

}

LinkedList *Player::getHandLL()
{
  return handLL;
}

/* returns player name */
std::string Player::getName()
{
    return name;
}

void Player::setName(std::string newName)
{
    this->name = newName;
}

void Player::setScore(int score)
{
    this->score = score;
}

Hand* Player::getHand()
{
    std::cout << "test in getHand: " << hand->handToString() << std::endl;
    return hand;
}

void Player::setHand(Hand* hand)
{
    this->hand = hand;
}


bool Player::checkIfTileInHand(int colour, int shape)
{
    bool exists;
    exists = hand->isTileInHand(colour, shape);
    return exists;
}

std::string Player::handToString()
{
    std::string handStr = "";
    Hand* hand = getHand();
    int size = hand->getSize();
    LinkedList* tiles = hand->getTiles();

    if ( (size = 0) ){

        std::cout << "Hand is empty" << std::endl;
    }
    else
    {
        for (int i = 0; i<size; i++)
        {
            char color = tiles->getTile(i)->getColour();
            int shape = tiles->getTile(i)->getShape();
            handStr.append(color + std::to_string(shape) + ",");
        }
        
    }
    return handStr;
}

void Player::replaceTile(char colour, int shape, TileBag* tileBag)
{
    tileBag->addTile(colour, shape);
    handLL->addFront(tileBag->drawTile());  
    //iterating through hand to find index of the tile to be removed
    int index = 0;
    for (int i = 0 ; i<handLL->getLength(); i++)
    {
        if ( (handLL->getTile(i)->getColour() == colour) 
        && (handLL->getTile(i)->getShape() == shape) )
        {
            index = i;
        }
    }
    // index was found, tile can now be removed
    handLL->deleteAtIndex(index);
}

void Player::fillPlayerhandFromFile(std::vector<std::string> vector)
{
    for(unsigned int i = 0; i < vector.size(); i++) 
    {    
        // create new tile using char[0] as colour and char[1] as shape

       /* convert to linked list structure */
        int shape = int(vector.at(i)[1]);
        Tile* tile = new Tile(vector.at(i)[0], shape); 
        handLL->addBack(tile);
    }
}

