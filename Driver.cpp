#include "Driver.h"
#include "TileCodes.h"

#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <iostream>

#define MAX_TILES_BAG 72
#define MAX_PLAYER_HAND 6
#define NO_OF_COLOR 6
#define NO_OF_SHAPE 6
#define ASCII_FOR_0 48
#define ID_OF_FIRST_PLAYER 1
#define ID_OF_SECOND_PLAYER 2
#define PLAY_GAME_SELECTION 1
#define LOAD_GAME_SELECTION 2
#define COMMAND_PLACE_TILE 4
#define COMMAND_REPLACE_TILE 2
#define COMMAND_SAVING_GAME 2


Driver::Driver() {
  this->playerCount = 0;
  tileBagStr = "";
}

Driver::~Driver() {

}

void Driver::getState(Player *p) {

  std::cout << "\n" << p->getPlayerName() << ", it's your turn." << std::endl;
  printScore();
  std::cout << std::endl;

  std::cout << board;
  std::cout << "\nYour hand is " << std::endl;
  p->displayTileInHand();

  std::cout << "\n> " << std::flush;
}

int Driver::countToken(std::string input) {
  int count = 0;

  std::string s1 = "";

  std::istringstream token(input);

  while (token >> s1) {
    count++;
  }

  return count;
}

void Driver::addPlayer(Player *p) {
  playerList[playerCount] = new Player(p->getPlayerId(), p->getPlayerName(),
      p->getPlayerHand());
  playerCount++;
}

void Driver::printScore() {
  for (int i = 0; i < this->playerCount; i++) {
    std::cout << "Score for " << playerList[i]->getPlayerName() << ": "
        << playerList[i]->getPlayerScore() << std::endl;
  }
}

Player* Driver::getTopScorePlayer(int i) {
  return topScoreplayer[i];
}

//Only if the command input conforms to the following format will validate format return true:
//format for placing: place <tile> at <location>
//replace format for replacing <tile>
//Taking a passing turn format: pass
bool Driver::validateFormat(std::string input) {
  bool result = false;

  std::regex place("^place ([ROYGBP][1-6]) at ([A-Z]([0-9]|1[0-9]|2[0-5]))");
  std::regex replace("^replace ([ROYGBP][1-6])");
  std::regex pass("pass");
  std::regex help("help");
  if (std::regex_match(input, place) || std::regex_match(input, replace)
      || std::regex_match(input, pass) || std::regex_match(input, help)) {
    result = true;
  }

  return result;
}

bool Driver::validateTileExistInHand(std::string tileInput,
    Player *player) {
  bool result = false;
  int size = tileInput.size();
  //tile is always represented by two characters.
  char char_array[size + 1];
  strcpy(char_array, tileInput.c_str());

  //Characters are converted to integers using ASCII.
  Tile *tileToBeCompare = new Tile(char_array[0], char_array[1] - ASCII_FOR_0);
  if (player->getPlayerHand()->contains(tileToBeCompare)) {
    result = true;
  }
  delete tileToBeCompare;

  return result;
}

//tile is positioned second in any command.
std::string Driver::getTileFromUserInput(std::string input) {

  std::string tile = "";

  std::istringstream token(input);

  //tile is positioned second in any command.
  for (int i = 0; i < 1; i++) {
    token >> tile;
  }
  token >> tile;

  return tile;
}

//location is at the fourth place in the placing instruction, thus we loop
//to get to the fourth position, three words must be tokenized.
std::string Driver::getLocationFromUserInput(std::string input) {
  std::string location = "";

  std::istringstream token(input);

  for (int i = 0; i < 3; i++) {
    token >> location;
  }

  token >> location;

  return location;
}

//Each time the user enters a saving command, this method will be invoked.
void Driver::saveGame(std::string filename, Player* player,
    LinkedList* tileBag) {
  //TO DO

}

//The second position of the saving command contains the filename
std::string Driver::getNameOfFileFromUserInput(std::string input) {
  std::string fileName = "";
  //TO DO
  

  return fileName;
}

void Driver::printMessageWhenSaveGame(std::string& inputFromUser,
    Player* player, LinkedList* tileBag, bool& quitGame) {
  //TO DO
  
}

void Driver::printMessageWhenInvalidFormat(std::string& inputFromUser,
    Player* player, LinkedList* tileBag, bool& quitGame, bool& ableToAdd) {
  while ((validateFormat(inputFromUser) == false
      || validateTileExistInHand(getTileFromUserInput(inputFromUser), player)
          == false) && quitGame != true) {
    if (inputFromUser.substr(0, 4)
        != "save"|| countToken(inputFromUser) != COMMAND_SAVING_GAME) {
      if (validateFormat(inputFromUser) == false) {
        std::cout << "\nUnacceptable Input, Recheck Your Format\n" << std::flush;

      } else if(inputFromUser == "help"){
        std::cout << "Use the following syntax to set a tile: 'place <tile> at <location'"
          "\nUse the following syntax for replacing a tile: 'replace <tile>'" << std::endl;
      }
      else if (validateTileExistInHand(inputFromUser, player) == false) {
        std::cout << "\nInvalid input; there are no tiles in your possession.\n" << std::flush;
      }

      std::cout << "> " << std::flush;
      ableToAdd = true;

      std::getline(std::cin, inputFromUser);
      if (std::cin.eof() == true) {
        addTopPlayer(getPlayerWithTopScoreWhenEnd());
        keepTopRecords();
        std::cout << "\n\nGoodbye" << std::endl;
        quitGame = true;

      }
    } else {
      if (countToken(inputFromUser) == 2) {
        //call saveGame() here
        saveGame(getNameOfFileFromUserInput(inputFromUser), player, tileBag);
        std::cout << "\nGame successfully saved\n\n" << std::endl;
        std::cout << "> " << std::flush;
        ableToAdd = true;
        std::getline(std::cin, inputFromUser);
        if (std::cin.eof() == true) {
          addTopPlayer(getPlayerWithTopScoreWhenEnd());
          keepTopRecords();
          std::cout << "\n\nGoodbye" << std::endl;
          quitGame = true;
        }
      }
    }
  }
}

void Driver::printInvalidWhenIllegalMove(bool& ableToAdd, bool& quitGame,
    std::string& inputFromUser) {
  if (ableToAdd == false) {
    std::cout << "\nIncorrect Input, Verify Your Move on the Board" << std::endl;
    std::cout << "> " << std::flush;

    std::getline(std::cin, inputFromUser);
    if (std::cin.eof() == true) {
      addTopPlayer(getPlayerWithTopScoreWhenEnd());
      keepTopRecords();
      std::cout << "\n\nGoodbye" << std::endl;
      quitGame = true;
    }
  }
}

void Driver::keepTopRecords() {
  //TO DO
}

//keeping all the moves in file "records.txt"
void Driver::keepRecords(std::string inputFromUser) {
  //TO DO
}

//get records as a one string
std::string Driver::getRecords() {
  std::string allMoves = "";
  //TO DO
  return allMoves;
}

//Design the player state from the saved file, paying attention to three factors:
//the player's name, score, and current hand of tiles
void Driver::designPlayerState(std::string& firstPlayerName,
    std::string& scoreFirstPlayer, std::string& firstPlayerHand,
    std::string& secondPlayerName, std::string& scoreSecondPlayer,
    std::string& secondPlayerHand) {
  int score_1 = 0;
  int score_2 = 0;

  LinkedList* firstPlayerHandLL = new LinkedList();
  LinkedList* secondPlayerHandLL = new LinkedList();

  std::string tmp = "";
  std::istringstream inputPlayerHand_1(firstPlayerHand);

  Player* firstPlayer = new Player(ID_OF_FIRST_PLAYER, firstPlayerName, firstPlayerHandLL);
  while (std::getline(inputPlayerHand_1, tmp, ',')) {
    char cTileArray[3];
    strcpy(cTileArray, tmp.c_str());
    Tile* tileToBeAdded = new Tile(cTileArray[0], cTileArray[1] - ASCII_FOR_0);
    firstPlayer->getPlayerHand()->addBack(tileToBeAdded);
    delete tileToBeAdded;
  }

  std::istringstream inputPlayerHand_2(secondPlayerHand);
  Player* secondPlayer = new Player(ID_OF_SECOND_PLAYER, secondPlayerName, secondPlayerHandLL);
  while (std::getline(inputPlayerHand_2, tmp, ',')) {
    char cTileArray[3];
    strcpy(cTileArray, tmp.c_str());
    Tile* tileToBeAdded = new Tile(cTileArray[0], cTileArray[1] - ASCII_FOR_0);
    secondPlayer->getPlayerHand()->addBack(tileToBeAdded);
    delete tileToBeAdded;
  }

  std::istringstream input_1(scoreFirstPlayer);
  input_1 >> score_1;
  std::istringstream input_2(scoreSecondPlayer);
  input_2 >> score_2;

  addPlayer(firstPlayer);
  addPlayer(secondPlayer);
  playerList[0]->setPlayerScore(score_1);
  playerList[1]->setPlayerScore(score_2);

  delete firstPlayer;
  delete secondPlayer;
}

void Driver::forwardTileBag(std::string& tileBagStr) {
  this->tileBagStr = tileBagStr;
}

//from saving a file, design tile bag
LinkedList* Driver::designTileBag(std::string& tileBag) {
  LinkedList* tileBagList = new LinkedList();
  //TO DO
  

  return tileBagList;

}

//based on all the movements read from the storing file, design board
//replay the game
void Driver::designBoard(std::string& moves) {
  std::string allMove = moves;

  //TO DO
}

//Players are prompted to continue placing tiles on the board after placing one tile.
void Driver::forPlaceMultipleTiles(bool& ableToAddTile,
    bool& firstPlayerTurn, bool& repromptPlayer, bool& quitGame, Player* player,
    LinkedList* tileBag) {
  bool passTurn = false;
  bool printState = true;
  std::string inputFromUser = "";
  int countTilePlacing = MAX_PLAYER_HAND
      - player->getPlayerHand()->getSize();

  do {
    if (printState == true) {
      getState(player);
      std::getline(std::cin, inputFromUser);
    }

    if (inputFromUser == "pass") {
      ableToAddTile = true;
      repromptPlayer = false;
      if (player->getPlayerId() == ID_OF_FIRST_PLAYER) {
        firstPlayerTurn = false;
      } else {
        firstPlayerTurn = true;
      }
      keepRecords(inputFromUser);
      passTurn = true;
    }

    else if (std::cin.eof() == true) {
      addTopPlayer(getPlayerWithTopScoreWhenEnd());
      keepTopRecords();
      std::cout << "\n\nGoodbye" << std::endl;
      passTurn = true;
      quitGame = true;
    }

    else {
      if (validateFormat(inputFromUser) == false
          || validateTileExistInHand(getTileFromUserInput(inputFromUser),
              player) == false || ableToAddTile == false) {
        if (validateFormat(inputFromUser) == false) {
          if (countToken(inputFromUser) == COMMAND_SAVING_GAME
              && inputFromUser.substr(0, 4) == "save") {
            std::cout << "\nGame successfully saved" << std::endl;
            std::string filename = getNameOfFileFromUserInput(inputFromUser);
            saveGame(filename, player, tileBag);
            std::cout << "> " << std::flush;

            std::getline(std::cin, inputFromUser);
          }
           else {
            std::cout << "Invalid input; format needs checking" << std::endl;
            std::cout << "> " << std::flush;
            std::getline(std::cin, inputFromUser);
          }
        } else if (validateTileExistInHand(getTileFromUserInput(inputFromUser),
            player) == false) {
              if(inputFromUser == "help"){
               std::cout << "Use the following syntax to set a tile: 'place <tile> at <location'"
                 "\nUse the following syntax for replacing a tile: 'replace <tile>'" << std::endl;
                 std::cout << "> " << std::flush;
                 std::getline(std::cin, inputFromUser);
               }
               else{
                 std::cout << "Invalid input; there is no tile input in the current hand." << std::endl;
                 std::cout << "> " << std::flush;
                 std::getline(std::cin, inputFromUser);
               }
        } else if (ableToAddTile == false) {
          std::cout << "Please double-check your move on the board due to an invalid input." << std::endl;
          std::cout << "> " << std::flush;
          std::getline(std::cin, inputFromUser);
          ableToAddTile = true;
        }

        printState = false;
      } else {

        if (countToken(inputFromUser) == COMMAND_PLACE_TILE) {

          std::string tileInput = getTileFromUserInput(inputFromUser);
          std::string gridLocation = getLocationFromUserInput(inputFromUser);
          if (validateFormat(inputFromUser) == true
              && validateTileExistInHand(tileInput, player) == true) {
            int size = tileInput.size();
            char cTileInput[size + 1];
            strcpy(cTileInput, tileInput.c_str());

            Tile *newTile = new Tile(cTileInput[0],
                cTileInput[1] - ASCII_FOR_0);

            if (gridLocation.size() == 2) {

              int sizeLocation = gridLocation.size();

              char cSizeInput[sizeLocation + 1];
              strcpy(cSizeInput, gridLocation.c_str());
              //cSizeInput[0] = y , cSizeInput[1] = x
              Synchronize c = Synchronize(cSizeInput[0],
                  cSizeInput[1] - ASCII_FOR_0, *newTile);

              if (!board.addTileAt(c)) {
                ableToAddTile = false;
                repromptPlayer = true;
                if (player->getPlayerId() == 2) {
                  firstPlayerTurn = false;
                }
                printState = false;
              } else {

                countTilePlacing++;
                player->getPlayerHand()->deleteTile(newTile);
                repromptPlayer = false;
                if (player->getPlayerId() == 2) {
                  firstPlayerTurn = true;
                }
                ableToAddTile = true;
                printState = true;
                keepRecords(inputFromUser);
              }
            }
            //Location on the grid is a three-char
            else {
              int sizeLocation = gridLocation.size();
              char cSizeInput[sizeLocation + 1];
              strcpy(cSizeInput, gridLocation.c_str());

              int x = (cSizeInput[1] - ASCII_FOR_0) * 10
                  + (cSizeInput[2] - ASCII_FOR_0);

              //cSizeInput[0] = y, x = x synchronize
              Synchronize c = Synchronize(cSizeInput[0], x, *newTile);
              if (!board.addTileAt(c)) {
                ableToAddTile = false;
                if (player->getPlayerId() == 2) {
                  firstPlayerTurn = false;
                }
                repromptPlayer = true;
                printState = false;
              } else {
                countTilePlacing++;
                player->getPlayerHand()->deleteTile(newTile);
                if (player->getPlayerId() == 2) {
                  firstPlayerTurn = true;
                }
                repromptPlayer = false;
                ableToAddTile = true;
                printState = true;
                keepRecords(inputFromUser);
              }
            }
            delete newTile;
          }
        } else {
          printState = false;
          std::cout
              << "\nYou can only continue putting tiles if the input is legitimate.\n" << std::endl;
          std::cout << ">" << std::flush;
          std::getline(std::cin, inputFromUser);
        }

      }
    }
  } while (passTurn == false);

  for (int i = 0; i < countTilePlacing; ++i) {
    player->getPlayerHand()->addBack(tileBag->getFront());
    tileBag->removeFront();
  }
  //only determine the final score once participants have finished arranging their tiles.
  player->setPlayerScore(board.totalPoint());
  
  board.resetValidation();
}

//This technique results in the game's flow.
void Driver::playGame(std::string player1Name, std::string player2Name, int selection) {

  //tilebag generated inside the parameters of playGame
  LinkedList* tileBag = nullptr;
  LinkedList* firstPlayerHand = new LinkedList();
  LinkedList* secondPlayerHand = new LinkedList();

  bool firstPlayerTurn = true;
  bool repromtFirstPlayer = true;
  bool repromptSecondPlayer = true;
  bool ableToAddTileForPlayer1 = true;
  bool ableToAddTileForPlayer2 = true;
  bool quitGame = false;

  std::string inputFromUser = "";
  std::string tileInput = "";
  std::string gridLocation = "";

  int turn = 0;

  //If users play a new game, we will create the game's state in this manner.
  if (selection == PLAY_GAME_SELECTION) {
    tileBag = new LinkedList();
    Player* firstPlayer = nullptr;
    Player* secondPlayer = nullptr;
    firstPlayer = new Player(ID_OF_FIRST_PLAYER, player1Name, firstPlayerHand);
    secondPlayer = new Player(ID_OF_SECOND_PLAYER, player2Name, secondPlayerHand);

    addPlayer(firstPlayer);
    addPlayer(secondPlayer);

    //shuffleTileBag(tileBag);
    //TO DO

    //tile bag for testing purpose - does not shuffle
    tileBagUnitTest(tileBag);

    setUpTilesInitially(firstPlayer, tileBag);
    setUpTilesInitially(secondPlayer, tileBag);
    delete firstPlayer;
    delete secondPlayer;
    //If a player chooses to load the game, we will have it set up in this manner.
  } else if (selection == LOAD_GAME_SELECTION) {

    
  }

  //game begins here
  do {
    if (firstPlayerTurn == true
        && playerList[0]->getPlayerHand()->getSize() == 6) {
      this->getState(playerList[0]);
      std::getline(std::cin, inputFromUser);
      if (std::cin.eof() == true) {
        addTopPlayer(getPlayerWithTopScoreWhenEnd());
        keepTopRecords();
        std::cout << "\n\nGoodbye" << std::endl;
        quitGame = true;
      }
    }

    //We do not need to check the permissible move on the board at the beginning of the game.
    if (turn == 0 && firstPlayerTurn == true) {
      //if player does not quit
      if (quitGame != true) {
        //begin asking the first player questions and validating here
        do {
          //This section deals with savegames and invalid input, such as invalidformat, invalidtileexistinhand, and invalidmove.
          if (validateFormat(inputFromUser) == false
              || validateTileExistInHand(getTileFromUserInput(inputFromUser),
                  playerList[0]) == false) {
            //Suppose a player uses this method's while loop to repeatedly save their game.
            printMessageWhenSaveGame(inputFromUser, playerList[0], tileBag,
                quitGame);
            printMessageWhenInvalidFormat(inputFromUser, playerList[0], tileBag,
                quitGame, ableToAddTileForPlayer1);
          }

          //Don't exit after saving invalid input. Here, the game continues to provide proof.
          //or entered properly the first time
          if (quitGame != true) {

            if (countToken(inputFromUser) == COMMAND_PLACE_TILE) {

              tileInput = getTileFromUserInput(inputFromUser);
              gridLocation = getLocationFromUserInput(inputFromUser);

              //proceeding to board validation after passing validateFormat and tileExistInHand
              if (validateFormat(inputFromUser) == true
                  && validateTileExistInHand(tileInput, playerList[0])
                      == true) {
                firstPlayerTurn = false;

                //compare with a c-style string.
                int size = tileInput.size();
                char cTileInput[size + 1];
                strcpy(cTileInput, tileInput.c_str());

                //using ASCII to convert char into integer
                Tile *newTile = new Tile(cTileInput[0],
                    cTileInput[1] - ASCII_FOR_0);

                if (gridLocation.size() == 2) {
                  int sizeLocation = gridLocation.size();

                  char cSizeInput[sizeLocation + 1];
                  strcpy(cSizeInput, gridLocation.c_str());

                  //using ASCII to convert char into integer
                  Synchronize c = Synchronize(cSizeInput[0],
                      cSizeInput[1] - ASCII_FOR_0, *newTile);
                  board.addTileAt(c);
                  ableToAddTileForPlayer1 = true;
                  playerList[0]->getPlayerHand()->deleteTile(newTile);
                  keepRecords(inputFromUser);
                  forPlaceMultipleTiles(ableToAddTileForPlayer1,
                      firstPlayerTurn, repromtFirstPlayer, quitGame,
                      playerList[0], tileBag);

                } else {
                  int sizeLocation = gridLocation.size();

                  char cSizeInput[sizeLocation + 1];
                  strcpy(cSizeInput, gridLocation.c_str());

                  int x = (cSizeInput[1] - ASCII_FOR_0) * 10
                      + (cSizeInput[2] - ASCII_FOR_0);

                  //cSizeInput[0] = y synchronize, x = x synchronize
                  Synchronize c = Synchronize(cSizeInput[0], x, *newTile);
                  board.addTileAt(c);

                  playerList[0]->getPlayerHand()->deleteTile(newTile);
                  ableToAddTileForPlayer1 = true;
                  keepRecords(inputFromUser);
                  forPlaceMultipleTiles(ableToAddTileForPlayer1,
                      firstPlayerTurn, repromtFirstPlayer, quitGame,
                      playerList[0], tileBag);
                }

                delete newTile;
                turn++;
                repromtFirstPlayer = false;
              }
            } else if (countToken(
                inputFromUser) == COMMAND_REPLACE_TILE) {
              tileInput = getTileFromUserInput(inputFromUser);
              if (validateFormat(inputFromUser)
                  && validateTileExistInHand(tileInput, playerList[0])) {

                firstPlayerTurn = false;

                int size = tileInput.size();
                char cTileInput[size + 1];
                strcpy(cTileInput, tileInput.c_str());

                Tile *newTile = new Tile(cTileInput[0],
                    cTileInput[1] - ASCII_FOR_0);

                tileBag->addBack(newTile);
                playerList[0]->getPlayerHand()->deleteTile(newTile);
                playerList[0]->getPlayerHand()->addBack(tileBag->getFront());
                tileBag->removeFront();

                delete newTile;

                ableToAddTileForPlayer1 = true;
                turn++;
                repromtFirstPlayer = false;

              }
            }
          }

        } while ((validateFormat(inputFromUser) == false
            || validateTileExistInHand(getTileFromUserInput(inputFromUser),
                playerList[0]) == false) && quitGame != true
            && repromtFirstPlayer == true && ableToAddTileForPlayer1 == false);
      }
      //not the initial turn
    } else if (turn != 0) {

      //If player 1 chooses not to leave, the game will begin validating input.
      if (quitGame != true) {
        //determining if a player's turn is their first or if they have previously made a move, and
        //can move on or keep putting tiles down.
        if (firstPlayerTurn
            == true&& playerList[0]->getPlayerHand()->getSize() == MAX_PLAYER_HAND) {

          //Now, begin encouraging player 1.
          do {
            //Goes into this thread is saveGame.
            if (validateFormat(inputFromUser) == false
                || validateTileExistInHand(getTileFromUserInput(inputFromUser),
                    playerList[0]) == false
                || ableToAddTileForPlayer1 == false) {
              //Suppose a player frequently saves a game.

              printMessageWhenSaveGame(inputFromUser, playerList[0], tileBag,
                  quitGame);
              printMessageWhenInvalidFormat(inputFromUser, playerList[0],
                  tileBag, quitGame, ableToAddTileForPlayer1);
              printInvalidWhenIllegalMove(ableToAddTileForPlayer1, quitGame,
                  inputFromUser);

            }
            //player does not quit
            if (quitGame != true) {

              if (countToken(inputFromUser) == COMMAND_PLACE_TILE) {

                tileInput = getTileFromUserInput(inputFromUser);
                gridLocation = getLocationFromUserInput(inputFromUser);

                if (validateFormat(inputFromUser) == true
                    && validateTileExistInHand(tileInput, playerList[0])
                        == true) {

                  int size = tileInput.size();
                  char cTileInput[size + 1];
                  strcpy(cTileInput, tileInput.c_str());

                  Tile *newTile = new Tile(cTileInput[0],
                      cTileInput[1] - ASCII_FOR_0);

                  if (gridLocation.size() == 2) {
                    int sizeLocation = gridLocation.size();

                    char cSizeInput[sizeLocation + 1];
                    strcpy(cSizeInput, gridLocation.c_str());
                    //cSizeInput[0] = y , cSizeInput[1] = x
                    Synchronize c = Synchronize(cSizeInput[0],
                        cSizeInput[1] - ASCII_FOR_0, *newTile);
                    if (!board.addTileAt(c)) {

                      ableToAddTileForPlayer1 = false;
                      firstPlayerTurn = true;
                      repromtFirstPlayer = true;
                    } else {

                      playerList[0]->getPlayerHand()->deleteTile(newTile);
                      keepRecords(inputFromUser);

                      ableToAddTileForPlayer1 = true;
                      firstPlayerTurn = false;
                      repromtFirstPlayer = false;
                      forPlaceMultipleTiles(ableToAddTileForPlayer1,
                          firstPlayerTurn, repromtFirstPlayer, quitGame,
                          playerList[0], tileBag);

                    }
                  } else {
                    int sizeLocation = gridLocation.size();

                    char cSizeInput[sizeLocation + 1];
                    strcpy(cSizeInput, gridLocation.c_str());

                    int x = (cSizeInput[1] - ASCII_FOR_0) * 10
                        + (cSizeInput[2] - ASCII_FOR_0);

                    Synchronize c = Synchronize(cSizeInput[0], x, *newTile);
                    if (!board.addTileAt(c)) {
                      ableToAddTileForPlayer1 = false;
                      firstPlayerTurn = true;
                      repromtFirstPlayer = true;
                    } else {

                      playerList[0]->getPlayerHand()->deleteTile(newTile);
                      ableToAddTileForPlayer1 = true;
                      firstPlayerTurn = false;
                      repromtFirstPlayer = false;
                      keepRecords(inputFromUser);
                      forPlaceMultipleTiles(ableToAddTileForPlayer1,
                          firstPlayerTurn, repromtFirstPlayer, quitGame,
                          playerList[0], tileBag);

                    }
                  }
                  delete newTile;
                  turn++;
                }
              } else if (countToken(
                  inputFromUser) == COMMAND_REPLACE_TILE) {
                tileInput = getTileFromUserInput(inputFromUser);
                if (validateFormat(inputFromUser)
                    && validateTileExistInHand(tileInput, playerList[0])) {

                  firstPlayerTurn = false;

                  int size = tileInput.size();
                  char cTileInput[size + 1];
                  strcpy(cTileInput, tileInput.c_str());

                  Tile *newTile = new Tile(cTileInput[0],
                      cTileInput[1] - ASCII_FOR_0);

                  tileBag->addBack(newTile);
                  playerList[0]->getPlayerHand()->deleteTile(newTile);
                  playerList[0]->getPlayerHand()->addBack(tileBag->getFront());
                  tileBag->removeFront();
                  delete newTile;

                  ableToAddTileForPlayer1 = true;
                  turn++;
                  repromtFirstPlayer = false;

                }
              }
            }
          } while ((validateFormat(inputFromUser) == false
              || validateTileExistInHand(getTileFromUserInput(inputFromUser),
                  playerList[0]) == false || ableToAddTileForPlayer1 == false)
              && quitGame != true && repromtFirstPlayer == true);
        } else if (playerList[0]->getPlayerHand()->getSize() != MAX_PLAYER_HAND) {

          forPlaceMultipleTiles(ableToAddTileForPlayer1,
              firstPlayerTurn, repromtFirstPlayer, quitGame, playerList[0],
              tileBag);
        }

        //Begin urging player 2 here for player 2's turn.
        if (quitGame != true&& firstPlayerTurn == false
        && playerList[1]->getPlayerHand()->getSize() == MAX_PLAYER_HAND) {

          this->getState(playerList[1]);

          std::getline(std::cin, inputFromUser);
          if (std::cin.eof()) {
            addTopPlayer(getPlayerWithTopScoreWhenEnd());
            keepTopRecords();
            std::cout << "\n\nGoodbye" << std::endl;
            quitGame = true;

          }

          //if player 2 decides not to end the game
          if (quitGame != true) {
            do {
              if (validateFormat(inputFromUser) == false
                  || validateTileExistInHand(
                      getTileFromUserInput(inputFromUser), playerList[1])
                      == false || ableToAddTileForPlayer2 == false) {
                printMessageWhenSaveGame(inputFromUser, playerList[1], tileBag,
                    quitGame);
                printMessageWhenInvalidFormat(inputFromUser, playerList[1],
                    tileBag, quitGame, ableToAddTileForPlayer2);
                printInvalidWhenIllegalMove(ableToAddTileForPlayer2, quitGame,
                    inputFromUser);
              }
              if (quitGame != true) {

                if (countToken(inputFromUser) == COMMAND_PLACE_TILE) {

                  tileInput = getTileFromUserInput(inputFromUser);
                  gridLocation = getLocationFromUserInput(inputFromUser);

                  if (validateFormat(inputFromUser) == true
                      && validateTileExistInHand(tileInput, playerList[1])) {

                    int size = tileInput.size();
                    char cTileInput[size + 1];
                    strcpy(cTileInput, tileInput.c_str());

                    Tile *newTile = new Tile(cTileInput[0],
                        cTileInput[1] - ASCII_FOR_0);

                    //grid location is a two-char A2
                    if (gridLocation.size() == 2) {
                      int sizeLocation = gridLocation.size();

                      char cSizeInput[sizeLocation + 1];
                      strcpy(cSizeInput, gridLocation.c_str());
                      //cSizeInput[0] = y , cSizeInput[1] = x
                      Synchronize c = Synchronize(cSizeInput[0],
                          cSizeInput[1] - ASCII_FOR_0, *newTile);

                      if (!board.addTileAt(c)) {
                        ableToAddTileForPlayer2 = false;
                        repromptSecondPlayer = true;
                        firstPlayerTurn = false;
                      } else {

                        playerList[1]->getPlayerHand()->deleteTile(newTile);

                        repromptSecondPlayer = false;
                        firstPlayerTurn = true;
                        ableToAddTileForPlayer2 = true;
                        keepRecords(inputFromUser);
                        forPlaceMultipleTiles(ableToAddTileForPlayer2,
                            firstPlayerTurn, repromptSecondPlayer, quitGame,
                            playerList[1], tileBag);

                      }
                    }
                    //grid location is a three-char
                    else {
                      int sizeLocation = gridLocation.size();

                      char cSizeInput[sizeLocation + 1];
                      strcpy(cSizeInput, gridLocation.c_str());

                      int x = (cSizeInput[1] - ASCII_FOR_0) * 10
                          + (cSizeInput[2] - ASCII_FOR_0);

                      //cSizeInput[0] = y, x = x synchronize
                      Synchronize c = Synchronize(cSizeInput[0], x, *newTile);
                      if (!board.addTileAt(c)) {
                        ableToAddTileForPlayer2 = false;
                        firstPlayerTurn = false;
                        repromptSecondPlayer = true;
                      } else {

                        playerList[1]->getPlayerHand()->deleteTile(newTile);

                        firstPlayerTurn = true;
                        repromptSecondPlayer = false;
                        ableToAddTileForPlayer2 = true;
                        keepRecords(inputFromUser);
                        forPlaceMultipleTiles(ableToAddTileForPlayer2,
                            firstPlayerTurn, repromptSecondPlayer, quitGame,
                            playerList[1], tileBag);

                      }
                    }
                    delete newTile;
                    turn++;
                  }
                } else if (countToken(
                    inputFromUser) == COMMAND_REPLACE_TILE) {

                  tileInput = getTileFromUserInput(inputFromUser);
                  if (validateFormat(inputFromUser)
                      && validateTileExistInHand(tileInput, playerList[1])) {

                    int size = tileInput.size();
                    char cTileInput[size + 1];
                    strcpy(cTileInput, tileInput.c_str());

                    Tile *newTile = new Tile(cTileInput[0],
                        cTileInput[1] - ASCII_FOR_0);
                    playerList[1]->getPlayerHand()->deleteTile(newTile);
                    tileBag->addBack(newTile);
                    playerList[1]->getPlayerHand()->addBack(
                        tileBag->getFront());
                    tileBag->removeFront();
                    delete newTile;

                    firstPlayerTurn = true;
                    ableToAddTileForPlayer2 = true;
                    turn++;
                    repromptSecondPlayer = false;
                  }
                }
              }

            } while ((validateFormat(inputFromUser) == false
                || validateTileExistInHand(getTileFromUserInput(inputFromUser),
                    playerList[1]) == false || ableToAddTileForPlayer2 == false)
                && quitGame != true && repromptSecondPlayer == true);
          }

        } else {
          forPlaceMultipleTiles(ableToAddTileForPlayer2,
              firstPlayerTurn, repromptSecondPlayer, quitGame, playerList[1],
              tileBag);
        }

      }
    }

  } while ((tileBag->getSize() != 0
      || ((playerList[0]->getPlayerHand()->getSize() != 0)
          && playerList[1]->getPlayerHand()->getSize() != 0))
      && quitGame != true);

  //only show once the game is over, not quitGame
  if (quitGame == false) {
    std::cout << "Game over" << std::endl;
    std::cout << "Score for " << playerList[0]->getPlayerName() << ": "
        << playerList[0]->getPlayerScore() << std::endl;
    std::cout << "Score for " << playerList[1]->getPlayerName() << ": "
        << playerList[1]->getPlayerScore() << std::endl;

    if (playerList[0]->getPlayerScore() > playerList[1]->getPlayerScore()) {
      std::cout << "Player " << playerList[0]->getPlayerScore() << " won!" << std::endl;
    } else {
      std::cout << "Player " << playerList[1]->getPlayerScore() << " won!" << std::endl;
    }
    addTopPlayer(getPlayerWithTopScoreWhenEnd());
    keepTopRecords();
    std::cout << "\n\nGoodbye" << std::endl;
  }

  delete firstPlayerHand;
  delete secondPlayerHand;
  if(selection == LOAD_GAME_SELECTION) {
    playerList[0]->clearPlayerHand();
    playerList[1]->clearPlayerHand();
  }
  delete playerList[0];
  delete playerList[1];
  delete tileBag;
}

Player* Driver::getPlayerWithTopScoreWhenEnd() {
   //TO DO
  return 0;
}

void Driver::addTopPlayer(Player* p) {
   //TO DO
}

//the call to playGame be forwarded
void Driver::load(std::string& playerTurn, int selection) {
   //TO DO
}

void Driver::setUpTilesInitially(Player *player, LinkedList *tileBag) {
  for (int i = 0; i < MAX_PLAYER_HAND; ++i) {
    player->getPlayerHand()->addBack(tileBag->getFront());
    tileBag->removeFront();
  }
}

int Driver::randomNumberGenerate() {
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, 5);

  return distr(eng);
}

//The formula is located in linkedlist.cpp.
void Driver::shuffleTileBag(LinkedList *tileBag) {
  //TO DO
}


//employing this technique when running unit tests in a game
void Driver::tileBagUnitTest(LinkedList* tileBag) {
  std::array<char, NO_OF_COLOR> colours = { RED, ORANGE, GREEN, BLUE,
  PURPLE, YELLOW };
  std::array<int, NO_OF_SHAPE> shapes = { CIRCLE, STAR_4, DIAMOND, SQUARE,
  STAR_6, CLOVER };

  std::default_random_engine engine(0);
  std::uniform_int_distribution<int> distr(0, 5);

  for (int count = 0; count < MAX_TILES_BAG; count++) {
    Tile *tileToBeAdded = new Tile(colours[distr(engine)],
        shapes[distr(engine)]);
    while (tileBag->tileExist(tileToBeAdded) == 2) {
      delete tileToBeAdded;
      tileToBeAdded = new Tile(colours[distr(engine)], shapes[distr(engine)]);
    }

    tileBag->addBack(tileToBeAdded);
    delete tileToBeAdded;
  }

}
