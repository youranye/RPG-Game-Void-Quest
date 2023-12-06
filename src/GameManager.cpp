#include "GameManager.h"
#include "Scene.h"

GameManager::GameManager(IOManager& ioManager, CharacterManager& characterManager, SceneManager& sceneManager)
    : ioManager(ioManager),characterManager(characterManager), sceneManager(sceneManager)
    {
    // Constructor logic
}

GameManager::~GameManager() 
{
    // Destructor logic
}

void GameManager::startGame() 
{
    bool gameFinished = false;
    while (!gameFinished) 
    {
        displayStartPage();

        
        int option;
        ioManager.write("Enter 'a' to start the game or 'b' for credits or 'c' to exit the game: ");
        option = ioManager.readOption(3); 

        switch (option) 
        {
            case 0:
                startGameLogic();
                break;
            case 1:
                displayCredits();
                waitForAnyChar(); // Wait for any character press to return to start page
                break;
            case 2:
                ioManager.write("GoodBye!\n");
                gameFinished = true;
                break;
            default:
                ioManager.write("Invalid choice. Please try again.\n");
                break;
        }
    }
}

void GameManager::displayStartPage() 
{
    ioManager.write("===== VoidQuest =====\n");
    ioManager.write("Welcome to VoidQuest, a text-based fantasy RPG! To play, enter the letter of the option you want to choose. \n");
    ioManager.write("a) Start game\n");
    ioManager.write("b) View credits.\n");
    ioManager.write("c) quit.\n");
}

void GameManager::displayCredits() 
{
    ioManager.write("===== Credits =====\n");
    ioManager.write("Game developed by Wen Wu Yiang, Youran Ye, Troy Drescher, Simone Laney. \n");
    ioManager.write("====== Story ======\n");
    ioManager.write("Story by Troy Drescher\n");
}

void GameManager::waitForAnyChar() 
{
    // Wait for the user to press any key to continue
    ioManager.write("Press any character to continue...");
    int input;
    input = ioManager.readOption(26); // Read and discard the input
}

void GameManager::startGameLogic() 
{
    // Implement your game logic here
    ioManager.write("Game is starting...\n");
    // Additional game initialization and logic
    ioManager.write("Welcome To GrimGard's Lair\n");
    characterManager.initialize();
    startSceneLogic("start#Start");
}

void GameManager::startSceneLogic(const std::string& firstSceneKey)
{
    sceneManager.replaceScene(firstSceneKey);
    //startSceneManager
    sceneManager.runScene();
    displayCredits();
}