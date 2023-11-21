#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "iomanager.h"

class GameManager {
public:
    GameManager(IOManager& ioManager, CharacterManager& characterManager, BattleManager& battleManager, SceneManager& sceneManager);
    ~GameManager();

    void startGame();

private:
    IOManager& ioManager;
    CharacterManager& characterManager;
    BattleManager& battleManager;
    SceneManager& sceneManager;
    bool isBattle; // Flag to identify if the next scene is a battle

    void displayStartPage();
    void displayCredits();
    void startGameLogic();
    void waitForAnyChar(); // Helper function to wait for any key press
    void handleNonBattleScene(BattleScene* currentScene);
    void handleBattleScene(BattleScene* currentScene);
    void goToNextScene(const std::string& nextSceneKey);
    bool isFinalSceneReached(); // Helper function to check if it's the final scene
};

#endif // GAMEMANAGER_H

