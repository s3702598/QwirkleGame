#include "LinkedList.h"

//constructor for linked list initialises head, tail and length 
LinkedList::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

// destructor for linked list 
 LinkedList::~LinkedList() 
{
   for(int i = 0; i < length; i++)
    {
		delete getTile(i);
    }
}

/* getter for the length*/
int LinkedList::getLength()
{
    return this->length;
}

/* getter for the head*/
Node* LinkedList::getHead()
{
    return this->head;
}


/* helper function to add a tile to the front of a list*/
void LinkedList::addFront(Tile* tile)
    {
        Node* newNode;
        // what  if RAM was full?
        try
        {
            newNode = new Node(tile, NULL);
        } 
        catch(const std::bad_alloc& e)
        {
            throw e;
        }
        
        if(this->head == NULL)
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            newNode->setNext(this->head);
            this->head = newNode;
        }
        this->length++;
    }

/* helper function to add a tile to the back of a list*/
void LinkedList::addBack(Tile* tile)
{
    Node* newNode = new Node(tile, NULL);
    if(this->head == NULL)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        tail->setNext(newNode);
        tail = newNode;
    }
    this->length++;
};

/* helper function to remove a tile from the front of a list*/
void LinkedList::removeFront()
{
    if (this->head == NULL)
    {
        throw std::exception();
    }
    else if (this->head == this->tail)
    {
        this->head = NULL;
        this->tail = NULL;
    }
    else
    {
        Node* temp = this->head;
        this->head = this->head->getNext();
        delete temp;
    }
    this->length--;
};

/* helper function to remove a tile from the back of a list*/        
void LinkedList::removeBack()
{
    if(this->head == NULL)
    {
        throw std::exception();
    }
    Node* temp = this->head;


    while(temp->getNext() != tail) // second last
    {
        temp = temp->getNext();
    }

    // temp is the second last 

    delete this->tail;
    temp->setNext(NULL);
    this->length--;
};


/* delete selected tile pointer */
void LinkedList::deleteAtIndex(int i)
{  
    // if first node
    if (i == 0)
    { 
        head = head->getNext();
        length--;
    }
    // if last node
    else if (i == length - 1)
    {
        removeBack();
    }
    else
    {
        findNode(i - 1)->setNext(findNode(i + 1));
        length--;
    } 

}

/* function to return ith element from the list */
Tile* LinkedList::getTile(int i) 
{
    if(i > this->getLength() || i < 0)
    {
        throw std::out_of_range("Index out of bounds");
    }
    else
    {
        Node* temp = this->head;
        int counter = 0;
        while(counter < i) 
        {
            temp = temp->getNext();
            counter++;
        }
        
        return temp->getTile();
    }
}

// Search for Node at index
Node* LinkedList::findNode(int i)
{
  Node* temp = head;

  for (int count = 1; count <= i; count++)
  {
    temp = temp->getNext();
  }
  return temp;
}

// Check if tile with matching color and shape exists in list
bool LinkedList::tileExists(char color, int shape){
	bool exists = false;
	Node* tNode = head;
	while(tNode != nullptr)
    {
		if(tNode->getTile()->getColour() == color && tNode->getTile()->getShape() == shape)
        {
			exists = true;
		}
		tNode = tNode->getNext();
	}
	return exists;
}


//  helper function to print out the list as a string 
std::vector<std::string> LinkedList::listToString(LinkedList* list)
{
    std::vector<std::string> tiles;
    Node* temp = list->head;
    if(temp == NULL)
    {
        std::cout << "Linked list is empty" << std::endl;
    }
    else
    {
        while (temp->getNext() != NULL)
        {
            Tile* tile = temp->getTile();
            char colour = tile->getColour(); 
            std::string shape = std::to_string(tile->getShape());// convert to char
            tiles.push_back(colour + shape + ","); 
            temp = temp->getNext();
        }
        
        Tile* tile = temp->getTile();
        char colour = tile->getColour();
        std::string shape = std::to_string(tile->getShape());// convert to char
        tiles.push_back(colour + shape); 
    }
    return tiles;
}


/* helper function to print list*/
void LinkedList::printAll()
{
    Node* temp = this->head;
    if(temp == NULL)
    {
        std::cout << "Linked list is empty" << std::endl;
    }
    else
    {
        while (temp != NULL)
        {
            std::cout << temp->getTile()->tileToString() << ",";
            temp = temp->getNext();
        }
    }
}

/* helper function to print list*/
std::string LinkedList::printString()
{
    std::string hand = "";
    Node* temp = this->head;
    if(temp == NULL)
    {
        std::cout << "Linked list is empty" << std::endl;
    }
    else
    {
        while (temp != NULL)
        {
            hand.append(temp->getTile()->tileToString() + ",");
            temp = temp->getNext();
        }
    }
    return hand;
}




