#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//#include "CharacterManager.h"
//#include "BattleManager.h"
#include "SceneManager.h"
//#include "IOManager.h"

class GameManager {
public:
    GameManager(IOManager& ioManager, CharacterManager& characterManager, SceneManager& sceneManager);
    ~GameManager();
    void startGame();

private:
    IOManager& ioManager;
    CharacterManager& characterManager;
    SceneManager& sceneManager;
    
    void displayStartPage();
    void displayCredits();
    void waitForAnyChar(); // Helper function to wait for any key press
    void startGameLogic();
    void startSceneLogic(const std::string& nextSceneKey);
};

#endif // GAMEMANAGER_H
