#include "gtest/gtest.h"
#include "BattleManager.h"
#include <iostream>

// Constructor tests
TEST(BattleManagerTests, TestConstructor)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);

    EXPECT_NO_THROW(BattleManager(player, enemy,ioManager));
}

TEST(BattleManagerTests, TestGetBattleOutcomeOngoing)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManager testBattle(player, enemy,ioManager);

    BattleOutcome battleStatus = testBattle.getBattleOutcome();

    EXPECT_EQ(battleStatus, ONGOING);
}