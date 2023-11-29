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

// runBattle tests
TEST(BattleManagerTests, TestRunBattle)
{
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    for(int i = 0; i < 40; i++) //add A's to input string so it will reach end of fight
    {
        ss << "a\n";
    }
    iss.str(ss.str());
    IOManager ioManager(iss,oss);
    BattleManager testBattle(player, enemy,ioManager);

    EXPECT_NO_THROW(testBattle.runBattle());
    EXPECT_TRUE( (testBattle.getBattleOutcome() == WIN) || (testBattle.getBattleOutcome() == DEATH) );
}

// getBattleOutcome tests
TEST(BattleManagerTests, TestGetBattleOutcomeWin)
{
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    Player* player = new Player("Elrond very fast",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,1,0,0,1);
    for(int i = 0; i < 40; i++) //add A's to input string so it will reach end of fight fast
    {
        ss << "a\n";
    }
    iss.str(ss.str());
    IOManager ioManager(iss,oss);
    BattleManager testBattle(player, enemy,ioManager);

    EXPECT_NO_THROW(testBattle.runBattle());
    //battle should be win since enemy has 0 attack and player has higher dex which means they go first and should hit with min 5 damage
    EXPECT_TRUE(testBattle.getBattleOutcome() == WIN);
}

TEST(BattleManagerTests, TestGetBattleOutcomeDeath)
{
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    Player* player = new Player("glass cannon",HUMAN,ROGUE,1,1000); //high sp so only can cast heal
    Character enemy = Character("ImpossibletoBeat",GOBLIN,ENEMY,5000,5000,500,90);
    for(int i = 0; i < 40; i++) //add b's to input string so it will reach end of fight fast
    {
        ss << 'b' << endl;
    }
    iss.str(ss.str());
    IOManager ioManager(iss,oss);
    BattleManager testBattle(player, enemy,ioManager);

    EXPECT_NO_THROW(testBattle.runBattle());
    //battle should be Death since player has 1 health and cannot deal damage, also goblin has max stats
    EXPECT_TRUE(testBattle.getBattleOutcome() == DEATH);
}
