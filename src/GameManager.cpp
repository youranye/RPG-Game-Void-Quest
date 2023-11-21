#include "GameManager.h"

GameManager::GameManager(IOManager& ioManager) : ioManager(ioManager) {
    // Constructor logic
}

GameManager::~GameManager() {
    // Destructor logic
}

void GameManager::startGame() {
    bool gameStarted = false;
    while (!gameStarted) {
        displayStartPage();

        int option;
        ioManager.write("Enter 'a' to start the game or 'b' for credits: ");
        option = ioManager.readOption(2); //A read function need to be added in the IOManager Class

        switch (option) {
            case 0:
                startGameLogic();
                gameStarted = true; // Exit loop when game starts
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