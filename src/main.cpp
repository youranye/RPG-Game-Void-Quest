#include "Character.h"
#include "BattleManager.h"
#include "GameManager.h"
#include "Player.h"
#include "IOManager.h"
#include <iostream>

using namespace std;

int main()
{
    //test to run BattleManager
    Player* player = new Player("Elrond",HUMAN,PLAYER,ROGUE,100,100);
    Character Enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,50,10,100);
    IOManager ioManager(cin,cout);
    BattleManager battleManager(player,Enemy,ioManager);
    battleManager.runBattle();

    return 0;
}