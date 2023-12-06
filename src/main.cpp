#include "GameManager.h"
#include "IOManager.h"
#include "CharacterManager.h"
#include "FileSceneStore.h"
#include <iostream>

using namespace std;

int main()
{
    IOManager ioManager{cin, cout};
    CharacterManager characterManager{ioManager};
    SceneManager sceneManager(std::make_unique<FileSceneStore>("./resources"), ioManager, characterManager);
    GameManager gm(ioManager, characterManager, sceneManager);
    gm.startGame();
    return 0;
}