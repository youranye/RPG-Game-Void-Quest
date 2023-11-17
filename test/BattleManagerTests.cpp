#include "gtest/gtest.h"
#include "BattleManager.h"

// Constructor tests
TEST(BattleManagerTests, TestConstructor)
{
    Character player("Abby", HUMAN, PLAYER, 15,12,5,20);
    Character enemy("Bill", HUMAN, ENEMY, 25, 9,5,10);

    EXPECT_NO_THROW(BattleManager(player, enemy));
}

// runBattle tests
TEST(BattleManagerTests, TestRunBattle)
{
    Character player("Abby", HUMAN, PLAYER, 5,25,5,20);
    Character enemy("Bill", HUMAN, ENEMY, 7,21,1,10);
    BattleManager testBattle(player, enemy);

    EXPECT_NO_THROW(testBattle.runBattle());
}

// getBattleOutcome tests
TEST(BattleManagerTests, TestGetBattleOutcomeOngoing)
{
    Character player("Abby", HUMAN, PLAYER, 15,12,5,20);
    Character enemy("Bill", HUMAN, ENEMY, 25, 9,5,10);
    BattleManager testBattle(player, enemy);

    BattleOutcome battleStatus = testBattle.getBattleOutcome();

    EXPECT_EQ(battleStatus, ONGOING);
}

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