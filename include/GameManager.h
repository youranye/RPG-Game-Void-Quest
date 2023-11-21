#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "iomanager.h"
#include "CharacterManager.h"
#include "BattleManager.h"
#include "SceneManager.h"
#include "NarrativeScene.h"
#include "BattleScene.h"

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
    void startGameLogic();
    void waitForAnyChar(); // Helper function to wait for any key press
    void displayScene();
    void startSceneLogic(const std::string& nextSceneKey);
    void handleNonBattleScene(NarrativeScene* currentScene);
    void handleBattleScene(BattleScene* currentScene);
    void goToNextScene(const std::string& nextSceneKey);
    bool isFinalSceneReached(); // Helper function to check if it's the final scene
};

#endif // GAMEMANAGER_H

