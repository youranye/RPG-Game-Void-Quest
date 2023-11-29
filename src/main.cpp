#include "Character.h"
#include "BattleManager.h"
#include "GameManager.h"
#include "Player.h"
#include "IOManager.h"
#include "CharacterManager.h"
#include "FileSceneStore.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    IOManager manager{cin, cout};
    CharacterManager characterManager{manager};
    SceneManager sceneManager(std::make_unique<FileSceneStore>("./resources"));
    GameManager gm(manager, characterManager, sceneManager);
    gm.startGame();
    return 0;
}