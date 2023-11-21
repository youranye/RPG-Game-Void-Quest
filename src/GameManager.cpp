#include "GameManager.h"

GameManager::GameManager(IOManager& ioManager) : ioManager(ioManager) {
    // Constructor logic
}

GameManager::~GameManager() {
    // Destructor logic
}

void GameManager::startGame() {
    while (true) {
        displayStartPage();

        int option;
        ioManager.write("Enter 'a' to start the game or 'b' for credits: ");
        option = ioManager.readOption(2); //A read function need to be added in the IOManager Class

        switch (option) {
            case 0:
                startGameLogic();
                startSceneLogic(); // Go to the next scene after starting the game
                break;
            case 1:
                displayCredits();
                waitForAnyChar(); // Wait for any character press to return to start page
                break;
            default:
                ioManager.write("Invalid choice. Please try again.\n");
                break;
        }

        if (isFinalSceneReached()) {
            ioManager.write("Reached final scene or game over. Returning to start page.\n");
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
    ioManager.write("Game developed by Wen Wu Yiang, Youran Ye, Troy Drescher, Simone Laney\n");
}

void GameManager::startGameLogic() {
    // Implement your game logic here
    ioManager.write("Game is starting...\n");
    // Additional game initialization and logic
}

void GameManager::waitForAnyChar() {
    // Wait for the user to press any key to continue
    ioManager.write("Press any character to continue...");
    int input;
    input = ioManager.readOption(26); // Read and discard the input
}

void GameManager::displayScene() {
    BattleScene* currentScene = sceneManager.getCurrentBattleScene();

    if (currentScene == nullptr) {
        ioManager.write("Error: Current scene not found.\n");
        return;
    }

    if (!currentScene->isBattle) {
        handleNonBattleScene(currentScene);
    } else {
        handleBattleScene(currentScene);
    }
}

void GameManager::handleNonBattleScene(BattleScene* currentScene) {
    ioManager.write(currentScene->getText());
    std::vector<std::string> options = currentScene->getOptions();

    // Get user option and implement scene transition logic here
    // Example:
    // int userChoice = ioManager.readOption(options.size());
    // Based on userChoice, transition to the next scene
    // ...
    goToNextScene(currentScene->getNextKey());
}

void GameManager::handleBattleScene(BattleScene* currentScene) {
    std::string enemyKey = currentScene->getEnemyName();
    Enemy* enemy = characterManager.getEnemy(enemyKey);

    if (enemy == nullptr) {
        ioManager.write("Error: Enemy not found.\n");
        return;
    }

    ioManager.write("Battle begins with enemy: " + enemyKey);

    // Run the battle with the obtained enemy using BattleManager
    bool playerWon = battleManager.runBattle(enemy);

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
