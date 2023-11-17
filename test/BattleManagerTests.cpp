#include "gtest/gtest.h"
#include "BattleManager.h"

// Constructor tests
TEST(BattleManagerTests, TestConstructor)
{
    Character player(15,90,12,11,20);
    Character enemy(25,60,9,15,10);

    EXPECT_NO_THROW(BattleManager(player, enemy));
}

// runBattle tests
TEST(BattleManagerTests, TestRunBattle)
{
    Character player(10,90,12,11,20);
    Character enemy(15,60,9,15,10);
    BattleManager testBattle(player, enemy);

    EXPECT_NO_THROW(testBattle.runBattle());
}

// getBattleOutcome tests
TEST(BattleManagerTests, TestGetBattleOutcomeOngoing)
{
    Character player(15,90,12,11,20);
    Character enemy(25,60,9,15,10);
    BattleManager testBattle(player, enemy);

    BattleOutcome battleStatus = testBattle.getBattleOutcome();

    EXPECT_EQ(battleStatus, ONGOING);
}

TEST(BattleManagerTests, TestGetBattleOutcomeWin)
{
    Character player(15,90,12,11,20);
    Character enemy(1,0,0,0,0);
    BattleManager testBattle(player, enemy);

    testBattle.runBattle();
    BattleOutcome result = testBattle.getBattleOutcome();

    EXPECT_EQ(result, WIN);
}

TEST(BattleManagerTests, TestGetBattleOutcomeDeath)
{
    Character player(1,0,0,0,0);
    Character enemy(25,60,9,15,10);
    BattleManager testBattle(player, enemy);

    testBattle.runBattle();
    BattleOutcome result = testBattle.getBattleOutcome();

    EXPECT_EQ(result, DEATH);
}