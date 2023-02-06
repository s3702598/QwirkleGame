#include "Driver.h"
#include "Board.h"
#include <iostream>
#include <array>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <regex>


// Strings are defined for code readability
#define GOODBYE_OPTION      "4"
#define GOODBYE             "\nGoodbye\n"
#define ERR_MENU_OPTION     "In order to choose a menu , please enter one of the numbers 1 to 4."
#define HELP_MENU_OPTION    "\nTo choose a menu , enter a number in the range of 1 to 4.\n"
#define GUIDE_NAME          "Your name must only contain capital letters. Please try again"
#define COUNT_PLAYERS        2
#define EXIT_SUCCESS    0

// Functions
void executeGame();
void playGame();
void loadGame();
void displayMenu();
void showPlayerInformation();
bool validateName(std::string playerName);
std::string inputNames(int player);
void showWhoseTurn(bool player1Turn);
bool validateHandFormat(std::string input);
// Array of 2 to hold player names
std::string storeNames[COUNT_PLAYERS];
bool player1Turn;
bool loadGameBool;


int main(void) 
{

    player1Turn = true;
    executeGame();



   //rememebr to delete everything that's new ;

   return EXIT_SUCCESS;
}

void executeGame() 
{
  std::string storevalue = "";
  std::string line;
  
  // Acsii number
  char b=219;
  
  // Horizontal spacing applied
  std::cout << "\n\n\t\t\t\t\t\tLoading Qwirkle Game!\n";
  std::cout<< "\t\t\t\t\t\t";
  for (int i=0;i<=15;i++)
  {
    // Prints ornamental line
    std:: cout<<b;
  }

  std::cout << "\n\nWelcome to Qwirkle!"
      "\n-------------------" << std::endl;

  do {
  try
  {
    displayMenu();
    std::cin >> storevalue;
    loadGameBool = false;

    // Validate storevalue
    // If user enters 'help' 
    if (storevalue == "help") {
      std::cout << HELP_MENU_OPTION << std::endl;
      // Or it's not the end of input - user enters more than one character
    } else if (!(std::cin.eof())
        // Or enters a value less than 1 
        // Convert string to integer
        and ((std::stoi(storevalue) < 1)
            // Or enters a greater than 4 or there is no input
            or (std::stoi(storevalue) > std::stoi(GOODBYE_OPTION)) or (!std::cin))) {
      // Clears error flag
      std::cin.clear();
      std::cout << ERR_MENU_OPTION << std::endl;
    } else {
      if (std::stoi(storevalue) == 1) {
        // Delete contents of file
        remove("records.txt");
        playGame();
        break;
      } else if (std::stoi(storevalue) == 2) {
        loadGameBool = true;
        playGame();
      } else if (std::stoi(storevalue) == 3) {
        showPlayerInformation();
      } else {
        // Flush function sends output to the terminal instantly (one by one) rather than once 
        std::cout << GOODBYE << std::flush;
      }
   }   
  }
  catch(const std::exception& e)
  {
    std::cerr << "Error! Program is terminating" << '\n';
  }

  // Continue until user enters '4'

  } while ((std::getline(std::cin, line))
      && (storevalue != "4"));
}

void playGame() {
  Driver* drLoad = new Driver();
  Driver* dr = new Driver("name1", "name2");
  Player* player1;
  Player* player2;
  TileBag* tileBag;
  int scoreP1, scoreP2;

  Board* board = new Board;
  // Clear previous input
  std::cin.ignore();

  if (loadGameBool == true)
  {
    std::cout << "\nLoading a Saved Game" << std::endl;
    // loading info from file
    drLoad = new Driver();
    
    std::tie(player1, player2,tileBag, board, player1Turn) = drLoad->fileLoad();
    storeNames[0] = player1->getName();
    storeNames[1] = player2->getName();
    scoreP1 = player1->getScore();
    scoreP2 = player2->getScore();
  }
  else
  {
    std::cout << "\nStarting a New Game" << std::endl;
    // new game always starts with player 1
    player1Turn = true;
    dr->fillPlayersHands(dr->getTileBag());

    storeNames[0] = inputNames(1);
    storeNames[1] = inputNames(2);
  
    std::ofstream myfile("records.txt");
    // Open file
    if (myfile.is_open())
    {
      myfile << storeNames[0] << "\n";
      myfile << storeNames[1] << "\n";
      // Close file
      myfile.close();
    }
    else
    {
      std::cout << "Unable to open file";
    }
    std::cout << "Let's Play!" << std::endl;

  }
  bool exited = false;
  while (!exited)
  {
    // if it's a new game, player 1 starts
    if (loadGameBool == false)
    {
      showWhoseTurn(player1Turn);
      dr->getPlayer("name1")->setName(storeNames[0]);
      dr->getPlayer("name2")->setName(storeNames[1]);
      scoreP1 = dr->getPlayer(storeNames[0])->getScore();
      std::cout << "Score for " << storeNames[0] << ": " << scoreP1 << std::endl;
      scoreP2 = dr->getPlayer(storeNames[1])->getScore();
      std::cout << "Score for " << storeNames[1] << ": " << scoreP2 << std::endl;
      // intitalising empty Board
      board = new Board();
      dr->printBoardGrid(board);
      std::cout << std::endl << std::endl;
      // show hand
      std::cout << "your hand is\n";
      if (player1Turn == true)
      {
        dr->getPlayer(storeNames[0])->getHandLL()->printAll();
      }
      else
      {
        dr->getPlayer(storeNames[1])->getHandLL()->printAll();
      }
    }
    else
    {
      showWhoseTurn(player1Turn);
      int scoreP1 = drLoad->getPlayer(storeNames[0])->getScore();
      std::cout << "Score for " << storeNames[0] << ": " << scoreP1 << std::endl;
      int scoreP2 = drLoad->getPlayer(storeNames[1])->getScore();
      std::cout << "Score for " << storeNames[1] << ": " << scoreP2 << std::endl;
      drLoad->printBoardGrid(board);
      std::cout << std::endl << std::endl;
      // show hand
      std::cout << "your hand is\n";
      if (player1Turn == true)
      {
        drLoad->getPlayer(storeNames[0])->getHandLL()->printAll();
      }
      else
      {
        drLoad->getPlayer(storeNames[1])->getHandLL()->printAll();
      }
    }
      
    std::cout << std::endl << std::endl << ">";

    // get input from user
    std::string userInput;
    getline(std::cin, userInput);

    while (validateHandFormat(userInput) == false)
    {
        std::cout << "You have entered Invalid input. Please enter again.\n>";
        getline(std::cin, userInput);
    }
  
    std::string endGame = "^D";

    if (userInput == endGame) {
        std::cout << GOODBYE << std::flush;
        exited = true;
    }
    else
    {
      if ((validateHandFormat(userInput) == true)) 
      {
        //tokenise user input to extract first word
        std::vector<std::string> tokens;
        std::stringstream check1(userInput);
        std::string temp;
        while (getline(check1, temp, ' '))
        {
            tokens.push_back(temp);
        }

        if (tokens[0] == "place") 
        {
          // 2nd token is the string to represent tile
          std::string tileStr = tokens[1];
          // 4th token is the position on board
          std::string positionStr = tokens[3];
          char rowCh = positionStr[0];
          // change from char to int by changing value from ASCII table
          int rPos = rowCh - 17;
          int cPos = positionStr[1];
          Tile* tile = new Tile(tileStr[0], tileStr[1]);
          bool canPlace = false;
          if (loadGameBool == false)
          {
            canPlace = dr->validatePlacing(tile, rPos, cPos, board);
          }
          else
          {
            canPlace = drLoad->validatePlacing(tile, rPos, cPos, board);
          }
          
          if ((canPlace = true)) 
          {
            board->placeTile(tile, rPos, cPos);
            // score points and draw tiles
            if (player1Turn == true)
            {
              if (loadGameBool == false)
              {
                dr->pointsScored(dr->getPlayer(storeNames[0]), board, rPos, cPos);
                dr->getPlayer(storeNames[0])->getHand()->drawTile(dr->getTileBag());
              }
              else
              {
                drLoad->pointsScored(dr->getPlayer(storeNames[0]), board, rPos, cPos);
                drLoad->getPlayer(storeNames[0])->getHand()->drawTile(dr->getTileBag());
              }
                
            }
            else
            {
              if (loadGameBool == false)
              {
                dr->pointsScored(dr->getPlayer(storeNames[1]), board, rPos, cPos);
                dr->getPlayer(storeNames[1])->getHand()->drawTile(dr->getTileBag());
              }
              else
              {
                drLoad->pointsScored(dr->getPlayer(storeNames[1]), board, rPos, cPos);
                drLoad->getPlayer(storeNames[1])->getHand()->drawTile(dr->getTileBag());
              }
            }
          }
          else {
              std::cout << "Can't place the tile on these coordinates! :(\n";
          }
        }
        else if (tokens[0] == "replace") 
        {
          std::string tileToReplace = tokens[1];
          char color = tileToReplace[0];
          int shape = tileToReplace[1];
          if (loadGameBool == false)
          {
            if (player1Turn == true)
            {
              dr->getPlayer(storeNames[0])->replaceTile(color, shape, dr->getTileBag());
            }
            else if (player1Turn == false)
            {
                dr->getPlayer(storeNames[1])->replaceTile(color, shape, dr->getTileBag());
            }  
          }
          else
          {
            if (player1Turn == true)
            {
              drLoad->getPlayer(storeNames[0])->replaceTile(color, shape, dr->getTileBag());
            }
            else if (player1Turn == false)
            {
              drLoad->getPlayer(storeNames[1])->replaceTile(color, shape, dr->getTileBag());
            } 
          }
        }
        else if (tokens[0] == "pass") {
            player1Turn = !player1Turn;
        }
        // help to be developed in week 11 and 12
        /* else if (tokens[0] == "help"){
        *  //help - overlay function to show help. exit back to this section
        *}
        */

        else if (tokens[0] == "s") {
          if (loadGameBool == false)
          {
            std::cout << "Enter game name to save\n>";
            dr->save();
          }
          else 
          {
            drLoad->save();
          }  
        }
      }
    }   
      // conclude turn by changing user
    player1Turn = !player1Turn;
  }
}


void loadGame() {

    std::cout << "\nNo Game To load Yet Comming Soon" << std::endl;
}

void displayMenu() {
  std::cout << "Menu\n"
      "1. New Game\n"
      "2. Load Game\n"
      "3. Show student information\n"
      "4. Quit\n"
      "> " << std::flush;
}

std::string inputNames(int player)
{
  bool baseValue = true;
  std::string playerName = "";

  do
  {
    if (baseValue)
    {
      std::cout << "Please enter a name for player " << player << " (uppercase characters only)" << std::endl;
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
      // Set to false
      baseValue = false;
    }
    // If name is invalid input
    else if (!validateName(playerName))
    {
      // Error message in #define
      std::cout << GUIDE_NAME << std::endl;
      // Prompt user to re-enter name
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
    }
    // Continue loop until player enters a valid name 
  } while (!validateName(playerName));
  return playerName;
}

bool validateName(std::string playerName)
{
  bool result = false;

  // Accepts any capital letter with a length of 1-25 characters

  std::regex name("[A-Z]{1,25}");
  if (std::regex_match(playerName, name))
  {
    result = true;
  }
  return result;
}

void showPlayerInformation() 
{
  std::cout << "---------------------------------------------" << std::endl;

  std::cout << "Name: Nathan Albinger" << std::endl;
  std::cout << "Student ID: s3670860" << std::endl;
  std::cout << "Email: s3670860@student.rmit.edu.au\n" << std::endl;

  std::cout << "Name: Jordan Edmondson" << std::endl;
  std::cout << "Student ID: s3779499" << std::endl;
  std::cout << "Email: s3779499@student.rmit.edu.au\n" << std::endl;
  
  std::cout << "Name: Finella Michael" << std::endl;
  std::cout << "Student ID: sxxxxxx" << std::endl;
  std::cout << "Email: sxxxxxxx@student.rmit.edu.au\n" << std::endl;

  std::cout << "Name: Honorata Trojanowska" << std::endl;
  std::cout << "Student ID: s3702598" << std::endl;
  std::cout << "Email: s3702598@student.rmit.edu.au" << std::endl;

  std::cout << "---------------------------------------------\n" << std::endl;
}

void showWhoseTurn(bool player1Turn)
{
  if (player1Turn == true)
  {
    std::cout << storeNames[0] <<", it's your turn\n" << std::endl;
  }
  else
  {
    std::cout << storeNames[1] <<", it's your turn\n" << std::endl;
  }
}

//Only if the command input conforms to the following format will validate format return true:
//format for placing: place <tile> at <location>
//replace format for replacing <tile>
//Taking a passing turn format: pass
bool validateHandFormat(std::string input) 
{
  bool result = false;

  std::regex place("^place ([ROYGBP][1-6]) at ([A-Z]([0-9]|1[0-9]|2[0-5]))");
  std::regex replace("^replace ([ROYGBP][1-6])");
  std::regex pass("pass");
  std::regex help("help");
  if (std::regex_match(input, place) || std::regex_match(input, replace)
      || std::regex_match(input, pass) || std::regex_match(input, help) 
      || input == "^D" || input == "s") 
  {
    result = true;
  }

  return result;
}






