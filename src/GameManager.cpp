#include "GameManager.h"
#include "Scene.h"

GameManager::GameManager(IOManager& ioManager, CharacterManager& characterManager, SceneManager& sceneManager, BattleManager& battleManager)
    : ioManager(ioManager),characterManager(characterManager), sceneManager(sceneManager), battleManager(battleManager)
    {
    // Constructor logic
}

GameManager::~GameManager() 
{
    // Destructor logic
}

void GameManager::startGame() 
{
    bool gameStarted = false;
    while (!gameStarted) 
    {
        displayStartPage();

        
        int option;
        ioManager.write("Enter 'a' to start the game or 'b' for credits: ");
        option = ioManager.readOption(2); 
        bool isDead = false;

        switch (option) 
        {
            case 0:
                gameStarted = true;
                characterManager.initialize();
             
                // TDOD: add isBattle to Scene, add isFinalScene to Scene
                
                while (!isDead) 
                {
                    Scene* currentScene = sceneManager.getCurrentScene();
                    // If current scene is battle scene, run battle
                    // if (currentScene->isBattle) 
                    // {
                    //     battleManager.runBattle();
                    //     BattleOutcome battleResult = battleManager.getBattleOutcome();
                    //     // If win, go to next scene
                    //     if(battleResult = WIN)
                    //     {
                    //         sceneManager.replaceScene(currentScene);
                    //     } 
                    //     // If die, scene loop terminates
                    //     else
                    //     {
                    //         isDead = true;
                    //         ioManager.write("Game over. \n")
                    //     }
                    // }
                    // else if(!currentScene->isBattle && !currentScene->isFinalScene)
                    // {
                    //     // If it's not a battle scene, replace the scene
                    //     sceneManager.replaceScene(currentScene);
                    // }
                    // else
                    // {
                    //     ioManager.write("Congratulations! It is the final scene. \n")
                    // }
                    isDead = true;
                }
                break;
            case 1:
                displayCredits();
                waitForAnyChar(); // Wait for any character press to return to start page
                break;
            default:
                ioManager.write("Invalid choice. Please try again.\n");
                break;
        }       
    }
}


void GameManager::displayStartPage() {
    ioManager.write("===== Void Quest =====\n");
    ioManager.write("Welcome to Void Quest, a text-based fantasy RPG! To play, enter the letter of the option you want to choose. \n");
    ioManager.write("a) Start game\n");
    ioManager.write("b) View credits.\n");
}

void GameManager::displayCredits() {
    ioManager.write("===== Credits =====\n");
    ioManager.write("Game developed by Wen Wu Yiang, Youran Ye, Troy Drescher, Simone Laney. \n");
}


void GameManager::waitForAnyChar() {
    // Wait for the user to press any key to continue
    ioManager.write("Press any character to continue...");
    int input;
    input = ioManager.readOption(26); // Read and discard the input
}

void GameManager::displayScene() {
    Scene* currentScene = sceneManager.getCurrentScene();

    if (currentScene == nullptr) {
        ioManager.write("Error: Current scene not found.\n");
        return;
    }
    
    // TDOD: add isBattle to Scene
    // if (!currentScene->isBattle) { 
    //     handleNonBattleScene(currentScene);
    // } else {
    //     handleBattleScene(currentScene);
    // }

    // handleNonBattleScene(sceneManager.getCurrentScene());
}

void GameManager::handleNonBattleScene(NarrativeScene* currentScene) {
    ioManager.write(currentScene->getText());
    std::vector<std::string> options = currentScene->getOptions();
    int userOption = ioManager.readOption(options.size());
    // Get user option and implement scene transition logic here
    // Example:
    // int userChoice = ioManager.readOption(options.size());
    // Based on userChoice, transition to the next scene
    // ...
    goToNextScene(currentScene->getKey(userOption));
}

void GameManager::handleBattleScene(BattleScene* currentScene) {
    std::string enemyKey = currentScene->getEnemyName();
    Character* enemy = &characterManager.getCharacter(enemyKey);

    if (enemy == nullptr) {
        ioManager.write("Error: Enemy not found.\n");
        return;
    }

    ioManager.write("Battle begins with enemy: " + enemyKey);

    // Run the battle with the obtained enemy using BattleManager
    Player* player = characterManager.getPlayer();
    BattleManager battleManager(player, *enemy, ioManager);
    battleManager.runBattle();
    bool playerWon = battleManager.getBattleOutcome();

    if (playerWon) {
        ioManager.write("You won the battle!\n");
    } else {
        ioManager.write("You lost the battle!\n");
    }

    goToNextScene(currentScene->getNextKey());
}

void GameManager::startSceneLogic(const std::string& nextSceneKey) {
    sceneManager.replaceScene(nextSceneKey);
    
}

bool GameManager::isFinalSceneReached() {
    // Logic to check if it's the final scene or game over
    // Replace this with your game over condition or final scene check
    // Example: Check if the current scene is the final scene
    return false;
}

void GameManager::goToNextScene(const std::string& nextSceneKey){

};
