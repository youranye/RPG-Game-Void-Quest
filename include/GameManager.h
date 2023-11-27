#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "CharacterManager.h"
#include "BattleManager.h"
#include "SceneManager.h"
#include "NarrativeScene.h"
#include "BattleScene.h"
#include "IOManager.h"

class GameManager {
public:
    GameManager(IOManager& ioManager, CharacterManager& characterManager, SceneManager& sceneManager, BattleManager& battleManager);
    ~GameManager();

    void startGame();

private:
    IOManager& ioManager;
    CharacterManager& characterManager;
    SceneManager& sceneManager;
    BattleManager& battleManager;
    
    void displayStartPage();
    void displayCredits();
    void waitForAnyChar(); // Helper function to wait for any key press
    void displayScene();
    void startSceneLogic(const std::string& nextSceneKey);
    void handleNonBattleScene(NarrativeScene* currentScene);
    void handleBattleScene(BattleScene* currentScene);
    void goToNextScene(const std::string& nextSceneKey);
    bool isFinalSceneReached(); // Helper function to check if it's the final scene
};

#endif // GAMEMANAGER_H
