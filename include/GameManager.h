#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "iomanager.h"

class GameManager {
public:
    GameManager(IOManager& ioManager);
    ~GameManager();

    void startGame();

private:
    IOManager& ioManager;
    void displayStartPage();
    void displayCredits();
    void startGameLogic();
    void waitForAnyChar(); // Helper function to wait for any key press
};

#endif // GAMEMANAGER_H
