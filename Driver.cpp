#include "Driver.h"

Driver::Driver(){}

Driver::Driver(std::string player1Name, std::string player2Name)
{
    // Starting new game with 26 cols and 26 rows
    // board = new Board(); - board got called in Main instead. Hono
    tileBag = new TileBag();
    player1 = new Player(player1Name, tileBag);
    player2 = new Player(player2Name, tileBag);
    players = {player1, player2};
    
}


// constructor for saved and loaded game
Driver::Driver(Player* player1, Player* player2, TileBag* tileBag, Board* board, bool player1Turn)

{
    // deref constructor parameters
    this->player1 = player1;
    this->player2 = player2;
    this->tileBag = tileBag;
    this->board = board;
    players = {player1, player2};
    this->player1Turn = player1Turn;
}

Driver::~Driver()
{
    delete board;
    delete tileBag;
}

//fills the hands of the player from the bag
void Driver::fillPlayersHands(TileBag* tileBag)
{
  player1->fillHand(tileBag);
  player2->fillHand(tileBag);
}

// boolean function checks if tile can be correctly placed
bool Driver::validatePlacing(Tile *tile, int rPos, int cPos, Board* board)
{
    bool canPlace = false;
    bool isPlacingOnEmptySpot = false;
    bool validPlacing = false;
    // Checking if entered position is within the Board
    bool isWithinBoardDimensions = board->posWithinBoard(rPos, cPos);
    bool noDupInLine = noDuplicateInLine(tile, rPos, cPos, board);

    if (isWithinBoardDimensions == true)
    {
        // Checking if requested position is empty
        isPlacingOnEmptySpot = isOnEmpty(rPos, cPos);

        if (isPlacingOnEmptySpot == true)
        {
            if ((noDupInLine = true)) 
            {
                // Checking Qwirkle rules for placing tiles
                validPlacing = isValidPlacing(tile, rPos, cPos);
            }
        }
    }
    // if requested position is within the board, empty and a valid placing, the tile can be placed
    if (isWithinBoardDimensions == true && isPlacingOnEmptySpot == true && validPlacing == true)
    {
        canPlace = true;
    }

    return canPlace;
}

// boolean function checks if tile is placed on empty space
bool Driver::isOnEmpty(int rPos, int cPos)
{
    bool isOnEmpty = false;
    if (board->posIsEmpty(rPos, cPos))
    {
        isOnEmpty = true;
    }
    return isOnEmpty;
}

// function checking if tile can be correctly placed
// following Qwirkle rules:
// position above, below, to the right and to the left
// needs to have matching color or shape
bool Driver::isValidPlacing(Tile *tile, int rPos, int cPos)
{

    bool canPlaceTile = false;
    bool nearCorrectTile = false;

    // if no tiles on the board, tile can be placed anywhere
    if (board->getNoOfTilesPlaced() == 0)
    {
        canPlaceTile = true;
    }

    // Checking if to the right has a tile
    if (board->getTile(rPos + 1, cPos) != nullptr)
    {
        // can't place if it's not next to matching color or shape
        if (nearColorOrShape(tile, rPos, cPos, rPos + 1, cPos) == false)
        {
            nearCorrectTile = false;
        }
    }
    // Checking if to the left has a tile
    if (board->getTile(rPos - 1, cPos) != nullptr)
    {
        // can't place if it's not next to matching color or shape
        if (nearColorOrShape(tile, rPos, cPos, rPos - 1, cPos) == false)
        {
            nearCorrectTile = false;
        }
    }
    // Checking if down has a tile
    if (board->getTile(rPos, cPos + 1) != nullptr)
    {
        // can't place if it's not next to matching color or shape
        if (nearColorOrShape(tile, rPos, cPos, rPos, cPos + 1) == false)
        {
            nearCorrectTile = false;
        }
    }
    // Checking if up has a tile
    if (board->getTile(rPos, cPos - 1) != nullptr)
    {
        // can't place if it's not next to matching color or shape
        if (nearColorOrShape(tile, rPos, cPos, rPos, cPos - 1) == false)
        {
            nearCorrectTile = false;
        }
    }

    // if it's next to a correct tile color or shape
    if (nearCorrectTile == true)
    {
        // Tile position must be by a piece already on t
        if (board->getTile(rPos + 1, cPos) == nullptr &&
            board->getTile(rPos - 1, cPos) == nullptr &&
            board->getTile(rPos, cPos + 1) == nullptr &&
            board->getTile(rPos, cPos - 1) == nullptr &&
            board->getNoOfTilesPlaced() > 0)
        {
            canPlaceTile = true;
        }
        else
        {
            canPlaceTile = false;
        }
    }
    return canPlaceTile;
}

// boolean function checks if tile matches the color or shape
bool Driver::nearColorOrShape(Tile *tile, int rPos, int cPos, int newRPos, int newCPos)
{
    bool isValid = false;
    // instatiating to 0
    int above = 0;
    int below = 0;
    int left = 0;
    int right = 0;

    // Checking 4 sides of the requested placing
    // incrmenting or decremnting depending on position
    if (newRPos == rPos + 1)
    {
        below++;
    }
    else if (newRPos == rPos - 1)
    {
        above--;
    }
    else if (newCPos == cPos + 1)
    {
        right++;
    }
    else if (newCPos == cPos - 1)
    {
        left--;
    }

    // Checking Row position of the current tile
    int checkRPos = rPos + above + below;
    // Checking Row position of the next tile by doubling the position coordinates
    int checkSecondRPos = rPos + (above + above) + (below + below);
    // Checking Column position of the current tile
    int checkCPos = cPos + left + right;
    // Checking Column position of the next tile by doubling the position coordinates
    int checkSecondCPos = cPos + (left + left) + (right + right);

    // get Color and shape of the tile to be placed
    Colour colour = tile->getColour();
    Shape shape = tile->getShape();
    // Tile pointer at current position
    Tile *currentPositionTilePtr = board->getTile(checkRPos, checkCPos);
    // Tile pointer at next position
    Tile *secondPositionTilePtr = board->getTile(checkSecondRPos, checkSecondCPos);

    // if color matches
    if (currentPositionTilePtr->getColour() == colour)
    {
        // if the place next to the tile is empty or matches color
        if (secondPositionTilePtr == nullptr || secondPositionTilePtr->getColour() == colour)
        {
           isValid = true;
        }
    }
    // if shape matches
    else if (currentPositionTilePtr->getShape() == shape)
    {
        // if the place next to the tile is empty or matches color
        if (secondPositionTilePtr == nullptr || secondPositionTilePtr->getShape() == shape)
        {
            isValid = true;
        }
    }
    return isValid;
}

//function to check if matching tile already exists in the same row or column
bool Driver::noDuplicateInLine(Tile* tile, int rPos, int cPos, Board* board){

    bool noDuplicateExists = true;

    // going through vector of tiles in the board
    std::vector<std::vector<Tile*>> tiles = board->getBoardVect();

    for (int r = 0 ; r< board->getNoOfRows(); r++){
        for (int c = 0; c<board->getNoOfCols(); c++){
            // get the row matching the tile to be placed
            if (r == rPos)
            {
                // check for tiles in the row
                if ( (tiles[r][c]->getColour() == tile->getColour()) 
                && (tiles[r][c]->getShape() == tile->getShape()) )
                {
                    noDuplicateExists = false;
                }
            }
            // get the column matching the tile to be placed
            if (c == cPos)
            {
                // check for tiles in the column
                if ( (tiles[r][c]->getColour() == tile->getColour()) 
                && (tiles[r][c]->getShape() == tile->getShape()) )
                {
                    noDuplicateExists = false;
                }
            }
            else
            {
                noDuplicateExists = true;
            }
        }
    }
    return noDuplicateExists;
}


// Calculate points that the player got during the round
void Driver::pointsScored(Player* player, Board* board, int rPos, int cPos){
    
    int rowPointsCount = calcPtsInRow(rPos, cPos, board);
    int colPointsCount = calcPtsInCol(rPos, cPos, board);
    int totalPointsScored = 0;


   // if first tile on the board, only 1 point
   if(board->getNoOfTilesPlaced() == 1)
	{
		totalPointsScored++;
    }
    else
    {
        totalPointsScored = rowPointsCount + colPointsCount +1;
    }

    //Setting the score
    int playersScore = player->getScore();
    player->setScore(playersScore + totalPointsScored);
}


// function calculating pounts from tiles above and below the placed tile
int Driver::calcPtsInRow(int rPos, int cPos, Board* board){

    // getting board vector
    std::vector<std::vector<Tile*>> tiles = board->getBoardVect();

    int pointsInLines = 0;
    int numOfTilesinLine = 0;

    for (int i = 0 ; i<board->getNoOfCols(); ++i)
    {
        if (tiles[i][cPos] != nullptr)
        {
            numOfTilesinLine++;
        }
    }
    // check column to the left and right of the tile
    if ((numOfTilesinLine = 1))
    {
        if (tiles[rPos-1][cPos] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos+1][cPos] != nullptr)
        {
            pointsInLines++;
        }
    }

    // check 2nd column to the left and right of the tile
    if ((numOfTilesinLine = 2))
    {
        if (tiles[rPos-2][cPos] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos+2][cPos] != nullptr)
        {
            pointsInLines++;
        }
    }
    // check 3rd column to the left and right of the tile
    if ((numOfTilesinLine = 3))
    {
        if (tiles[rPos-3][cPos] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos+3][cPos] != nullptr)
        {
            pointsInLines++;
        }
    }
    // check 4th column to the left and right of the tile
    if ((numOfTilesinLine = 4))
    {
        if (tiles[rPos-4][cPos] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos+4][cPos] != nullptr)
        {
            pointsInLines++;
        }
    }
    // check 5th column to the left and right of the tile
    // if 6 tiles in line - Qwirkle
    if ((numOfTilesinLine > 4))
    {
        if (tiles[rPos-5][cPos] != nullptr)
        {
            pointsInLines= pointsInLines+6;
            std::cout << "Qwirkle! <3" << std::endl;
        }
        if (tiles[rPos+5][cPos] != nullptr)
        {
            pointsInLines= pointsInLines+6;
            std::cout << "Qwirkle! <3" << std::endl;
        }
    }
    // no need to check more than 5 rows as only 6 tiles can be in line
    return pointsInLines;
}

/* function calculating pounts from tiles
* to the left and right of the placed tile
*/
int Driver::calcPtsInCol(int rPos, int cPos, Board* board){

    // getting board vector
    std::vector<std::vector<Tile*>> tiles = board->getBoardVect();
    int pointsInLines = 0;
    int numOfTilesinLine = 0;

    for (int i = 0 ; i<board->getNoOfRows(); ++i)
    {
        if (tiles[rPos][i] != nullptr)
        {
            numOfTilesinLine++;
        }
    }
    // check column to the left and right of the tile
    if ((numOfTilesinLine = 1))
    {
        if (tiles[rPos][cPos-1] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos][cPos+1] != nullptr)
        {
            pointsInLines++;
        }
    }

    // check 2nd column to the left and right of the tile
    if ((numOfTilesinLine = 2))
    {
        if (tiles[rPos][cPos-2] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos][cPos+2] != nullptr)
        {
            pointsInLines++;
        }
    }
    // check 3rd column to the left and right of the tile
    if ((numOfTilesinLine = 3))
    {
        if (tiles[rPos][cPos-3] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos][cPos+3] != nullptr)
        {
            pointsInLines++;
        }
    }
    // check 4th column to the left and right of the tile
    if ((numOfTilesinLine = 4))
    {
        if (tiles[rPos][cPos-4] != nullptr)
        {
            pointsInLines++;
        }
        if (tiles[rPos][cPos+4] != nullptr)
        {
            pointsInLines++;
        }
    }
    // check 5th column to the left and right of the tile
    if ((numOfTilesinLine > 4))
    {
        if (tiles[rPos][cPos-5] != nullptr)
        {
            pointsInLines= pointsInLines+6;
            std::cout << "Qwirkle! <3" << std::endl;
        }
        if (tiles[rPos][cPos+5] != nullptr)
        {
            pointsInLines= pointsInLines+6;
            std::cout << "Qwirkle! <3" << std::endl;
        }
    }
    // no need to check more than 5 columns as only 6 tiles can be in line
    // this is checked when validating placing
    return pointsInLines;
}




/* Ask user for file to load, check if file can be opened and print message 
* create a string vector to capture content, items separated by whitespace... */
std::tuple<Player*, Player*, TileBag*, Board*, bool> Driver::fileLoad()
{
    std::string name;
    std::string extension = ".input";
    std::cout << "Input file to load..." << std::endl;
    std::cout << ">";
    std::cin >> name;
    std::string fileName = name + extension;
    std::ifstream file (fileName);
    try
    {
        // create variables to contain the input from file

        int player1Score;
        int player2Score;
        std::string player1Hand;
        std::string player2Hand;
        std::string boardShape;
        std::vector<std::string> boardStates;
        std::vector<std::string> p1H;
        std::vector<std::string> p2H;
        std::vector<std::string> tBag;
        std::vector<std::string> bShape;
        std::string input;
        std::string bag;
        std::string currentPlayer;


        if(file.is_open())
        {
            std::cout << "Loading " << fileName << std::endl;
        }
        else
        {
            std::cerr << "Error loading " << fileName << std::endl;
        }

        // read the input into variables
        file >> player1Name //ascii
                >> player1Score //is int
                >> player1Hand // convert to linked list
                >> player2Name //ascii
                >> player2Score // is int
                >> player2Hand // convert to linked list
                >> boardShape; // convert to vector

        // read to string input until newLine and then add to vector
        while((file >> input) && (file.peek() != '\n')) //reads until '\n', but not the last item
        {
            boardStates.push_back(input);
        }
        boardStates.push_back(input); // add final el in boardStates

        file >> bag // convert to linked list
                >> currentPlayer;


        p1H = stringToVector(player1Hand, p1H); // convert player1 hand to vector
        p2H = stringToVector(player2Hand, p2H); // convert player2 hand to vector
        tBag = stringToVector(bag, tBag); // convert tileBag string to vector

        // convert boardShape string to vect, this ensures whole int if boardSize goes into double digits
        bShape = stringToVector(boardShape, bShape); 
        std::string columnString = bShape.at(0);
        int col = stringToInt(columnString); // convert bShape to int col

        std::string rowString = bShape.at(1);
        int row = stringToInt(rowString); // bShape is string row

        // construct new hands based on the file stringstreams
        LinkedList* hand1 = new LinkedList(); //handLLFromVector(p1H); // segfault
        for(unsigned int i = 0; i < p1H.size(); i++) 
        {    
        // create new tile using char[0] as colour and char[1] as shape
        /* convert to linked list structure */
            int shape = char(p1H.at(i)[1]) - 48;
            Tile* tile = new Tile(p1H.at(i)[0], shape); 
            hand1->addBack(tile);
        }
        LinkedList* hand2 = new LinkedList(); //handLLFromVector(p2H); // segfault

        for(unsigned int i = 0; i < p2H.size(); i++) 
        {    
            // create new tile using char[0] as colour and char[1] as shape

        /* convert to linked list structure */
            int shape = char(p2H.at(i)[1]) - 48;
            Tile* tile = new Tile(p2H.at(i)[0], shape); 
            hand2->addBack(tile);
        }    

        // construct tileBag based on file stringstream
        tileBag = new TileBag(tBag);

        // construct new players based on the file input
        player1 = new Player(player1Name, hand1, player1Score); // segfault
        player2 = new Player(player2Name, hand2, player2Score); // segfault

        // construct  board based on file stringstream
        board = new Board(col, row);
        tilesOnBoard(boardStates, board);  
        if(currentPlayer != player1Name)
        {
            player1Turn = false;
        }
        player1Turn = true;
        
    }
    catch(const std::exception& e)
    {
         std::cerr << e.what() << '\n';
    }
    file.close();
    return std::make_tuple(player1, player2, tileBag, board, player1Turn); 
}


// save current game state
/* Ask user for name to save file to, and display appropriate message
save uoutput as text file */
void Driver::save()
{
    
    std::string name;
    std::string extension = ".output";
    std::cout << ">";
    std::cin >> name;
    std::string fileName = name + extension;
    std::ofstream file(fileName.c_str());

    try
    {
        if (file.is_open())
        {
            std::cout << "Success" << std::endl;
        }
        else
        {
            std::cerr << "Error, problem mounting file" << std::endl;
        }
        
        //note whose turn it is
        std::string currentPlayer = "";
        if (player1Turn == true)
        {
            currentPlayer = player1Name;
        } 
        else
        {
            currentPlayer = player2Name;
        }

        // LinkedList* hand1LL = player1->getHandLL();
        // std::vector<std::string> player1HandString = hand1LL->listToString(hand1LL);
        // LinkedList* hand2LL = player2->getHandLL();
        // std::vector<std::string> player2HandString = hand2LL->listToString(hand2LL);

        // prints hand to console----------------------------------------------------------------
        std::string player1HandAsString = getPlayer(player1->getName())->getHandLL()->printString();
        std::string player2HandAsString = getPlayer(player2->getName())->getHandLL()->printString();

        //output to file
        file << player1->getName() << std::endl;
        file << player1->getScore() << std::endl;
        file << player1HandAsString << std::endl;

        file << player2->getName() << std::endl;
        file << player2->getScore() << std::endl;
        file << player2HandAsString << std::endl;
        
        file << board->boardShape() << std::endl;
        file << board->boardToString() << std::endl;
        file << tileBag->bagToString() << std::endl;
        file << currentPlayer << std::endl;

        }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    file.close();
}

void Driver::printBoard(Board *board)
{
    std::cout << board->boardToString() << std::endl;
}

// printing vector of tiles
void Driver::printBoardGrid(Board* board)
{
    std::cout << board->printBoardGrid() << std::endl;
}

Player* Driver::getPlayer(std::string name)
{

    if (name == player1->getName())
    {
        return player1;
        std::cout << "in getPlayer: " << player1->getName() << std::endl;
    }
    else
    {
        return player2;
    }
}

TileBag* Driver::getTileBag()
{
    return this->tileBag;
}


std::vector<std::string> Driver::stringToVector(std::string str, std::vector<std::string> vect)
{
    std::stringstream s_stream(str); //create string stream from the string
    while(s_stream.good()) 
    {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        vect.push_back(substr);
    }
   return vect;
}

// helper to convert string to int 
int Driver::stringToInt(std::string num) 
{
    std::stringstream string;
    string << num;
    int n;
    string >> n;
    return n;
}


// helper to take the board state and split it into tiles and positions
Board* Driver::tilesOnBoard(std::vector<std::string>vect, Board* board)    
{
    // for each boardState... set tile attributes via string 
    for(unsigned int i = 0; i < vect.size(); i++) 
    {    
        // create new tile using char[0] as colour and charToInt char[1] as shape

        std::string shape(1, vect.at(i)[1]);
        int number = std::stoi(shape);
        // int isShape = vect.at(i)[1]; 
        Tile* tile = new Tile(vect.at(i)[0], number); 
        
        // set position attributes
        // requires conversion to number as per grid A-Z is 1-26
        char c = vect.at(i)[3];
        int row = int(c)-64;
        
        
        std::string colString1(1, vect.at(i)[4]);
        int col;
        if(vect.at(i)[5] != ',')
        {
            std::string colString2(1, vect.at(i)[5]);
            std::string colString = colString1 + colString2;
            col = std::stoi(colString);
        }
        else
        {
            col = std::stoi(colString1);
        }
        
        //place the tile
        board->placeTile(tile, row, col);
    }
    return board;
}


//fills the hands of the player from the bag
void Driver::loadHandsFromFile(std::vector<std::string> vector1,std::vector<std::string> vector2)
{
  player1->fillPlayerhandFromFile(vector1);
  player2->fillPlayerhandFromFile(vector2);
}

// function taking list of tiles from vector and returning linked list
LinkedList* Driver::handLLFromVector(std::vector<std::string> vector)
{
    LinkedList* handLinkedList = nullptr;
    for(unsigned int i = 0; i < vector.size(); i++) 
    {    
        // create new tile using char[0] as colour and char[1] as shape

       /* convert to linked list structure */
        int shape = int(vector.at(i)[1]);
        Tile* tile = new Tile(vector.at(i)[0], shape); 
        handLinkedList->addBack(tile);
    }
    return handLinkedList;
}



