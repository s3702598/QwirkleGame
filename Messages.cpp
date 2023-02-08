
#include "Messages.h"
#include "TileCodes.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>

#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_COLOR 6
#define NUMBER_OF_SHAPE 6
#define NUMBER_OF_TILES_IN_PLAYER_HAND 6
#define NUMBER_OF_COMMAS 5
#define NUMBER_OF_TILES_TOTAL 72
#define LINE_INF_ABOUT_PLAYER 6
#define HIGH_SCORE_LIST 1

#define GOODBYE_OPTION  "4"
#define GOODBYE "\nGoodbye\n"
#define ERR_MENU_OPTION "Invalid input; please enter one of the messeges options from 1 to 5.."
#define ERR_FILE_FORMAT "ERROR: The file name you supplied is incorrectly formatted; the file cannot be loaded.."
#define GUIDE_NAME "Your name must only contain capital letters. Please try once more."
#define ERR_FILE_NOT_EXIST "Please try again if your file does not exist.."
#define HELP_MENU_OPTION "\nTo pick one of the message choices, please input a number between 1 and 5.\n"
#define COUNT_PLAYERS  2

Messages::Messages() {
  driver = Driver();
}

void Messages::executeGame() {
  std::string userInput = "";
  std::string line;

  std::cout << "\n\nWelcome to Qwirkle!"
      "\n-------------------" << std::endl;

  do {
    printMenu();
    std::cin >> userInput;

    // Validate userInput
    if (userInput == "help") {
      std::cout << HELP_MENU_OPTION << std::endl;
    } else if (!(std::cin.eof())
        and ((std::stoi(userInput) < 1)
            or (std::stoi(userInput) > std::stoi(GOODBYE_OPTION)) or (!std::cin))) {
      std::cin.clear();
      std::cout << ERR_MENU_OPTION << std::endl;
    } else {
      if (std::stoi(userInput) == 1) {
        remove("records.txt");
        playGame();
      } else if (std::stoi(userInput) == 2) {
        load();
      } else if (std::stoi(userInput) == 3) {
        showStudentInformation();
      } else {
        std::cout << GOODBYE << std::flush;
      }
    }
  } while ((std::getline(std::cin, line))
      && (userInput != "4"));
}

void Messages::playGame() {
  //clear whitespace from previous input before use getline()
  std::cin.ignore();

  std::string playerNames[COUNT_PLAYERS];

  std::cout << "\nStarting a New Game" << std::endl;

  playerNames[0] = inputNames(1);
  playerNames[1] = inputNames(2);

  std::cout << "Let's Play!" << std::endl;
  driver.playGame(playerNames[0], playerNames[1], 1); //Need to adjust this for multiplayers
}

bool Messages::validateName(std::string playerName) {
  bool result = false;

  // Only accept UPPERCASE CHARACTERS 1-25 inclusive in length
  std::regex name("[A-Z]{1,25}");
  if (std::regex_match(playerName, name)) {
    result = true;
  }
  return result;
}

std::string Messages::inputNames(int player) {
  bool initialPrompt = true;
  std::string playerName = "";

  do {
    if (initialPrompt) {
      std::cout << "Please enter a name for player " << player
          << " (uppercase characters only)" << std::endl;
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
      initialPrompt = false;
    }
// If name is invalid input
    else if (!validateName(playerName)) {
      std::cout << GUIDE_NAME << std::endl;
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
    }
  } while (!validateName(playerName));
  return playerName;
}

bool Messages::checkFileExist(std::string& fileName) {
 //TO DO
  return 0;
}

bool Messages::checkFormatForPlayerHand(std::string& playerHand) {

  bool result = true;
  std::vector<std::string> tokens;
  std::string tmp = "";
  std::istringstream input(playerHand);
  std::regex tileFormat("([ROYGBP][1-6])");

  while (std::getline(input, tmp, ',')) {
    //each tokens = tile
    tokens.push_back(tmp);
  }

  for (unsigned int i = 0; i < tokens.size() && result == true; ++i) {
    if (std::regex_match(tokens[i], tileFormat) == false) {
      result = false;
    }
  }
  return result;
}

bool Messages::validateFormat(std::string& fileName) {
  std::ifstream input(fileName);
  bool result = true;

  std::string playerName[NUMBER_OF_PLAYERS];
  int playerScore = 0;
  std::string playerHand = "";
  std::string tileBag = "";
  std::regex tileFormat("([ROYGBP][1-6])");

  for (int i = 0; i < NUMBER_OF_PLAYERS && result == true; ++i) {
    std::getline(input, playerName[i]);

    input >> playerScore;

    //consume whitespace
    input >> std::ws;

    if (input.good()) {

      std::getline(input, playerHand);
      if (validateName(playerName[i]) == false
          || checkFormatForPlayerHand(playerHand) == false) {
        result = false;

      }
    } else {
      result = false;
    }
  }

  if (result == true) {
    std::string tmp = "";
    std::getline(input, tileBag);

    std::istringstream inString(tileBag);

    while (std::getline(inString, tmp, ',') && result == true) {
      if (std::regex_match(tmp, tileFormat) == false) {
        result = false;
      }
    }
  }

  if (result == true) {
    std::string tmp = "";
    while (std::getline(input, tmp) && result == true) {
      if (driver.validateFormat(tmp) == false) {
        if (tmp != playerName[0] && tmp != playerName[1]) {
          result = false;
        }
      }
    }
  }

  return result;
}

void Messages::keepRecordFileInSyncWithSavingFile(std::string& fileName) {
  //TO DO
}

void Messages::load() {
  //TO DO
  
}

void Messages::printMenu() {
  std::cout << "Messages\n"
      "1. New Game\n"
      "2. Load Game\n"
      "3. (Credits)Show student information\n"
      "4. Quit\n"
      "> " << std::flush;
}

void Messages::showStudentInformation() {
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


