#include "Board.h"

// New Game Constructor

Board::Board()
{
    noOfCols = 26;
    noOfRows = 26;

    // resizing the vector to match board dimensions
    board.resize(noOfRows);

    for (int r = 0; r < noOfRows; ++r)
    {
        for (int c = 0; c < noOfCols; ++c)
        {
            board[r].push_back(nullptr);
        }
    }

    //initialising to 0 at the start of the game
    noOfTilesPlaced = 0 ;
}



Board::Board(int noOfCols, int noOfRows)
{
    this->noOfCols = noOfCols;
    this->noOfRows = noOfRows;

    // resizing the vector to match board dimensions
    board.resize(noOfRows);

    for (int r = 0; r < noOfRows; ++r)
    {
        for (int c = 0; c < noOfCols; ++c)
        {
            board[r].push_back(nullptr);
        }
    }

    //initialising to 0 at the start of the game
    noOfTilesPlaced = 0 ;
}

//Destructor
Board::~Board()
{
    board.clear();

}

// getter for number of columns
int Board::getNoOfCols()
{
    return noOfCols;
}

// getter for number of rows
int Board::getNoOfRows()
{
    return noOfRows;
}

// getter for number of tiles placed
int Board::getNoOfTilesPlaced()
{
    return noOfTilesPlaced;
}

// Checking if posistion is within the Board
bool Board::posWithinBoard(int rPos, int cPos)
{
    
    bool isWithinBoard = false;
    
	 if((rPos > 0 || rPos <= noOfRows) &&
	   (cPos > 0 || cPos <= noOfCols))
	{
		isWithinBoard = true;
	}
    return isWithinBoard;
}

Tile* Board::getTile(int rPos, int cPos){

    // if position is outside the board, return null pointer
    bool isOutsideBoard = !(posWithinBoard(rPos, cPos));
    if((isOutsideBoard = true))
	{
		return nullptr;
	}

	return board[rPos][cPos];
}

//Checking if position is empty
bool Board::posIsEmpty(int rPos, int cPos)
{
	bool isEmpty = false;
	// If null pointer at this coordinate, it's empty
	if(board[rPos][cPos] == nullptr)
	{
		isEmpty = true;
	}
	return isEmpty;
}

// Places a tile without checking the game rules
// Checking game rules is in the Driver Class
void Board::placeTile(Tile *tile, int rPos, int cPos)
{
    board[rPos][cPos] = tile;
    noOfTilesPlaced++;
}

/* Helper function to printout size of Board at gameSave*/
std::string Board::boardShape()
{
    // Conversion of int into string using to_string()
    std::string rows = std::to_string(noOfRows);
    std::string cols = std::to_string(noOfCols);
    std::string result = (rows + "," + cols);
    return result;
}

// /* Helper function to printout tiles on Board at gameSave*/
std::string Board::printBoardGrid()
{
    std::string boardString = "";
    // passing values from board vector from .h
    std::vector<std::vector<Tile*>> tiles = board;

    //printing first line
    for (int c = 1 ; c<=26; ++c)
    {

        if (c == 1 )
        {
            boardString.append("   ");
        }

        if (c < 10)
        {
            boardString.append(std::to_string(c));
            boardString.append("  ");
        }
        if (c > 9)
        {
            boardString.append(std::to_string(c));
            boardString.append(" ");
        }
    }
    boardString.append("\n");
    // printing second and third line
    for(int c = 1; c < 26; c++)
	{
		if(c == 1)
		{
			boardString.append("  ");
		}
		boardString.append("---");
	}
    boardString.append("---");
    boardString.append("\n");

    for(int r = 1; r <= 26; r++)
	{
        // printing row names
        std::string rowName = "";
        // capital letter in ASCII start at 65
		char rowChar = 64 + r;
		rowName = rowChar;
		
		boardString.append(rowName + " |");
		
		for(int c = 1; c <= 26; c++)
		{
            // below is printing empty board, without printing tiles on board
            // first column was printed so we need to print columns 2 to 26
			if (c > 1 && c <= 27 )
            {
                boardString.append("  |");
            }

            /*
            // below is code is suppoused to print board with tiles on it
            // causes segmentation error on tileToString() function - Honorata
            
            if(tiles[r][c] == nullptr)
			{
				boardString.append("  |");
			}
			else
			{
                
				boardString.append(board[r][c]->tileToString() + "|");
			}
            
            */
		}
		if(r <= 26)
		{
			boardString.append("  |\n");	
		}
	}
	return boardString;
}
    
std::string Board::boardToString(){
    std::string boardStr = "";
    for (int i = 0; i < noOfRows; i++)
    {
        for (int j = 0; j < noOfCols; j++)
        {
            if(!posIsEmpty(i, j)) // tile exists
            {
                std::string colour = std::to_string(board[i][j]->getColour()); 
                std::string shape = std::to_string(board[i][j]->getShape());
                std::string row = std::to_string(i);
                std::string col = std::to_string(j);
                boardStr.append(colour + shape + "@" + row + col + ",");
            }  
        }   
    }
    return boardStr;
}

 std::vector<std::vector<Tile*>> Board::getBoardVect(){
    return board;
 }
