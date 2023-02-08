#ifndef ASSIGNMENT_2_MENU
#define ASSIGNMENT_2_MENU

#include "Driver.h"

class Messages {

  public:

    Messages();
    void executeGame();
    void playGame();
    void load();

    void printMenu();
    void showStudentInformation();
    std::string inputNames(int player);
    bool validateName(std::string playerName);

    bool checkFileExist(std::string& fileName);
    bool validateFormat(std::string& fileName);
    bool checkFormatForPlayerHand(std::string& playerHand);

    void keepRecordFileInSyncWithSavingFile(std::string& fileName);
  private:
    Driver driver;

};

#endif //ASSIGNMENT_2_MENU
