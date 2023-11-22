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

// runBattle tests TODO: fix for updated class
/*
TEST(BattleManagerTests, TestRunBattle)
{
    Character player("Abby", HUMAN, PLAYER, 5,25,5,20);
    Character enemy("Bill", HUMAN, ENEMY, 7,21,1,10);
    BattleManager testBattle(player, enemy);

    EXPECT_NO_THROW(testBattle.runBattle());
}
// getBattleOutcome tests

TEST(BattleManagerTests, TestGetBattleOutcomeWin)
{
    Character player("Abby", HUMAN, PLAYER, 15,12,5,20);
    Character enemy("Bill", HUMAN, ENEMY, 1, 0,0,0);
    BattleManager testBattle(player, enemy);

    testBattle.runBattle();
    BattleOutcome result = testBattle.getBattleOutcome();

    EXPECT_EQ(result, WIN);
}

TEST(BattleManagerTests, TestGetBattleOutcomeDeath)
{
    Character player("Abby", HUMAN, PLAYER, 1,0,0,0);
    Character enemy("Bill", HUMAN, ENEMY, 25, 9,5,10);
    BattleManager testBattle(player, enemy);

    testBattle.runBattle();
    BattleOutcome result = testBattle.getBattleOutcome();

    EXPECT_EQ(result, DEATH);
}
*/