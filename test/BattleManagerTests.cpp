#include "gtest/gtest.h"
#include "BattleManager.h"
#include "Player.h"
#include "Character.h"
#include <iostream>

// Constructor tests
TEST(BattleManagerTests, TestConstructor)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);

    EXPECT_NO_THROW(BattleManager(player, enemy,ioManager));
    delete player;
    player = nullptr;
}

// getBattleOutcome tests
TEST(BattleManagerTests, TestGetBattleOutcomeOngoing)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManager testBattle(player, enemy,ioManager);

    BattleOutcome battleStatus = testBattle.getBattleOutcome();

    EXPECT_EQ(battleStatus, ONGOING);
    delete player;
    player = nullptr;
}

// Rand Tests
class BattleManagerFixtureRandTest : public BattleManager 
{
public:
    BattleManagerFixtureRandTest(Player* playerCharacter, Character& enemyCharacter, IOManager& ioManager)
            : BattleManager(playerCharacter,enemyCharacter,ioManager) {}
    int pubRandNumGenerator(int lowest, int highest)
    {
        return randNumGenerator(lowest,highest);
    }
};

TEST(BattleManagerTests, TestRandZeroToHundred)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);

    BattleManagerFixtureRandTest battleManager(player, enemy, ioManager);
    int lowest = 0;
    int highest = 100;
    int num = battleManager.pubRandNumGenerator(lowest,highest);
    EXPECT_TRUE(num >= lowest);
    EXPECT_TRUE(num <= highest);

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestRandZeroToFifty)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);

    BattleManagerFixtureRandTest battleManager(player, enemy, ioManager);
    int lowest = 0;
    int highest = 50;
    int num = battleManager.pubRandNumGenerator(lowest,highest);
    EXPECT_TRUE(num >= lowest);
    EXPECT_TRUE(num <= highest);

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestRandFiveToSix)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);

    BattleManagerFixtureRandTest battleManager(player, enemy, ioManager);
    int lowest = 5;
    int highest = 6;
    int num = battleManager.pubRandNumGenerator(lowest,highest);
    EXPECT_TRUE(num >= lowest);
    EXPECT_TRUE(num <= highest);

    delete player;
    player = nullptr;
}

// Indepth Tests

// Testing functions that don't involve rand.
class BattleManagerFixture : public BattleManager 
{
public:
    BattleManagerFixture(Player* playerCharacter, Character& enemyCharacter, IOManager& ioManager)
            : BattleManager(playerCharacter,enemyCharacter,ioManager) {}
    int pubChooseAction() 
    {
        return chooseAction();
    }
    int pubDetermineAttackSuccess(int accuracy, int dodge)
    {
        return determineAttackSuccess(accuracy,dodge);
    }
    int pubCalculateDamage(int attackPower, int attackMod, int targetDefense, int defenseMod, int hitValue)
    {
        return calculateDamage(attackPower,attackMod,targetDefense,defenseMod,hitValue);
    }
    void pubDisplayAttack(bool isSpecial, bool isPlayer, int success, int damage)
    {
        displayAttack(isSpecial,isPlayer,success,damage);
    }
    void pubDisplayHeal(bool isPlayer, int amount)
    {
        displayHeal(isPlayer, amount);
    }
};

// Test the user choosing their action
TEST(BattleManagerTests, TestFixtureChooseActionAttack)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "a\n";
    iss.str(ss.str());
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    EXPECT_EQ(testBattle.pubChooseAction(), 0);

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureChooseActionHeal)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "b\n";
    iss.str(ss.str());
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    EXPECT_EQ(testBattle.pubChooseAction(), 1);

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureChooseActionSpecialAttack)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "c\n";
    iss.str(ss.str());
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    EXPECT_EQ(testBattle.pubChooseAction(), 2);

    delete player;
    player = nullptr;
}




// Test the determination of attack success
TEST(BattleManagerTests, TestFixtureDetermineAttackSuccessAccurracyLessThanDodge)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    int accuracy = 10;
    int dodge = 20;
    EXPECT_EQ(testBattle.pubDetermineAttackSuccess(accuracy,dodge),0);
    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDetermineAttackSuccessAccurracyMoreThanDodge)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    int accuracy = 20;
    int dodge = 10;
    EXPECT_EQ(testBattle.pubDetermineAttackSuccess(accuracy,dodge),1);
    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDetermineAttackSuccessCritical)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    int accuracy = 90;
    int dodge = 20;
    EXPECT_EQ(testBattle.pubDetermineAttackSuccess(accuracy,dodge),2);
    delete player;
    player = nullptr;
}

// test damage calculation
TEST(BattleManagerTests, TestFixtureCalculateDamage)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    int attackPower = 20;
    int attackMod = 10;
    int targetDefense = 10;
    int defenseMod = 10;
    int hitValue = 1;
    int expected = ((attackPower * attackMod) - (targetDefense * defenseMod)) * hitValue * 0.3;
    EXPECT_EQ(testBattle.pubCalculateDamage(attackPower,attackMod,targetDefense,defenseMod,hitValue),expected);
    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureCalculateDamageOnMiss)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    int attackPower = 20;
    int attackMod = 10;
    int targetDefense = 10;
    int defenseMod = 10;
    int hitValue = 0;
    int expected = ((attackPower * attackMod) - (targetDefense * defenseMod)) * hitValue * 0.3;
    EXPECT_EQ(testBattle.pubCalculateDamage(attackPower,attackMod,targetDefense,defenseMod,hitValue),expected);
    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureCalculateDamageOnCritical)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    IOManager ioManager(cin,cout);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    int attackPower = 20;
    int attackMod = 10;
    int targetDefense = 10;
    int defenseMod = 10;
    int hitValue = 2;
    int expected = ((attackPower * attackMod) - (targetDefense * defenseMod)) * hitValue * 0.3;
    EXPECT_EQ(testBattle.pubCalculateDamage(attackPower,attackMod,targetDefense,defenseMod,hitValue),expected);
    delete player;
    player = nullptr;
}

// test display of the results of different actions
TEST(BattleManagerTests, TestFixtureDisplayHealPlayer)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "you cast Heal and heal " << 10 << " hp!\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayHeal(1,10);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplayHealEnemy)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "Barry the Goblin" << " casts Heal and heals " << 10 << " hp!\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayHeal(0,10);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplayAttackPlayerRogue)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "You try to plunge your dagger into " << enemy.getName() << " and you drop your dagger on the ground\n";
    ss << "You swing your dagger at " << enemy.getName() << " and deal " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << "You plunge your dagger into " << enemy.getName() << " and deal " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(0,1,0,0);
    testBattle.pubDisplayAttack(0,1,1,1);
    testBattle.pubDisplayAttack(0,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplayAttackPlayerWarlock)
{
    Player* player = new Player("Elrond",HUMAN,WARLOCK,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "You try to hit " << enemy.getName() << " with your staff and you miss completely\n";
    ss << "You bash " << enemy.getName() << " with your staff and deal " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << "You try to bash " << enemy.getName() << " with your staff and cast a fireball dealing " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(0,1,0,0);
    testBattle.pubDisplayAttack(0,1,1,1);
    testBattle.pubDisplayAttack(0,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplayAttackPlayerPaladin)
{
    Player* player = new Player("Elrond",HUMAN,PALADIN,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "You try to swing your sword at " << enemy.getName() << " and your sword flies right out of your hand\n";
    ss << "You swing your sword at " << enemy.getName() << " and you deal " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << "You swing your sword at " << enemy.getName() << " and you cast fireball dealing " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(0,1,0,0);
    testBattle.pubDisplayAttack(0,1,1,1);
    testBattle.pubDisplayAttack(0,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplayAttackPlayerForged)
{
    Player* player = new Player("Elrond",DWARF,FORGED,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << "You try to swing your axe at " << enemy.getName() << " and your axe flies right out of your hand\n";
    ss << "You swing your axe down on " << enemy.getName() << " and your axe deals " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << "You Hurl your axe at " << enemy.getName() << " and your axe deals " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(0,1,0,0);
    testBattle.pubDisplayAttack(0,1,1,1);
    testBattle.pubDisplayAttack(0,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplaySpecialAttackPlayerRogue)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << player->getAbility().description << " dealing " << 0 << " damage to " << enemy.getName() << "\n";
    ss << player->getAbility().description << " dealing " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << player->getAbility().description << " dealing " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(1,1,0,0);
    testBattle.pubDisplayAttack(1,1,1,1);
    testBattle.pubDisplayAttack(1,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplaySpecialAttackPlayerWarlock)
{
    Player* player = new Player("Elrond",HUMAN,WARLOCK,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << player->getAbility().description << " dealing " << 0 << " damage to " << enemy.getName() << "\n";
    ss << player->getAbility().description << " dealing " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << player->getAbility().description << " dealing " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(1,1,0,0);
    testBattle.pubDisplayAttack(1,1,1,1);
    testBattle.pubDisplayAttack(1,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplaySpecialAttackPlayerPaladin)
{
    Player* player = new Player("Elrond",HUMAN,PALADIN,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << player->getAbility().description << " dealing " << 0 << " damage to " << enemy.getName() << "\n";
    ss << player->getAbility().description << " dealing " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << player->getAbility().description << " dealing " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(1,1,0,0);
    testBattle.pubDisplayAttack(1,1,1,1);
    testBattle.pubDisplayAttack(1,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

TEST(BattleManagerTests, TestFixtureDisplaySpecialAttackPlayerForged)
{
    Player* player = new Player("Elrond",DWARF,FORGED,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::stringstream ss;
    std::istringstream iss;
    std::ostringstream oss;
    ss << player->getAbility().description << " dealing " << 0 << " damage to " << enemy.getName() << "\n";
    ss << player->getAbility().description << " dealing " << 1 << " damage to " << enemy.getName() << "\n";
    ss << "Critical Hit!\n" << player->getAbility().description << " dealing " << 2 << " damage to " << enemy.getName() << "\n";
    IOManager ioManager(iss,oss);
    BattleManagerFixture testBattle(player, enemy,ioManager);
    testBattle.pubDisplayAttack(1,1,0,0);
    testBattle.pubDisplayAttack(1,1,1,1);
    testBattle.pubDisplayAttack(1,1,2,2);
    EXPECT_EQ(oss.str(),ss.str());

    delete player;
    player = nullptr;
}

// uses a fixed value that can be set in place of a randomly generated number
class BattleManagerFixtureRandFixedValTest : public BattleManager 
{
public:
    BattleManagerFixtureRandFixedValTest(Player* playerCharacter, Character& enemyCharacter, IOManager& ioManager)
            : BattleManager(playerCharacter,enemyCharacter,ioManager) {}
    int randVal = 0;
    int randNumGenerator(int lowest, int highest)
    {
        return randVal;
    }
    void setRandNum(int value)
    {
        randVal = value;
    }
    void pubAttack(bool isPlayerAttacker)
    {
        attack(isPlayerAttacker);
    }
    void pubSpecialAttack(bool isPlayer)
    {
        specialAttack(isPlayer);
    }
    void pubHeal(bool isPlayer)
    {
        heal(isPlayer);
    }
};

// Testing Battle with preset action for Player to allow for testing runBattle
class BattleManagerFixtureRunBattleTest : public BattleManager 
{
protected:
    int ActionToReturn = 0;
    int chooseAction()
    {
        player->regenerateSP(100); //regen sp in case they run out
        return ActionToReturn;
    }
public:
    BattleManagerFixtureRunBattleTest(Player* playerCharacter, Character& enemyCharacter, IOManager& ioManager)
            : BattleManager(playerCharacter,enemyCharacter,ioManager) {}
    void setAction(int num)
    {
        ActionToReturn = num;
    }
};

// Test that the battle runs and an outcome is recorded
TEST(BattleManagerTests, TestFixtureRunBattleOnlyAttack)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,110,15,10,15);
    std::istringstream iss;
    std::ostringstream oss;
    IOManager ioManager(iss,oss);
    BattleManagerFixtureRunBattleTest testBattle(player, enemy,ioManager);

    EXPECT_NO_THROW(testBattle.runBattle());
    EXPECT_TRUE( (testBattle.getBattleOutcome() == WIN) || (testBattle.getBattleOutcome() == DEATH) );
}

TEST(BattleManagerTests, TestFixtureRunBattleOnlySpecialAttack)
{
    Player* player = new Player("Elrond",HUMAN,ROGUE,2000,1000);
    Character enemy = Character("???",VOIDWALKER,BOSS,3000,100,100,90,Ability("???",ATTACK,"hits you",NONE,150,50));
    std::istringstream iss;
    std::ostringstream oss;
    IOManager ioManager(iss,oss);
    BattleManagerFixtureRunBattleTest testBattle(player, enemy,ioManager);
    testBattle.setAction(2);
    EXPECT_NO_THROW(testBattle.runBattle());
    EXPECT_TRUE( (testBattle.getBattleOutcome() == WIN) || (testBattle.getBattleOutcome() == DEATH) );
}

// Test that a player and win and lose using a rigged battle
TEST(BattleManagerTests, TestFixtureGetBattleOutcomeWin)
{
    Player* player = new Player("Elrond very fast",HUMAN,ROGUE,200,100);
    Character enemy = Character("Barry the Goblin",GOBLIN,ENEMY,1,0,0,1);
    std::istringstream iss;
    std::ostringstream oss;
    IOManager ioManager(iss,oss);
    BattleManagerFixtureRunBattleTest testBattle(player, enemy,ioManager);

    EXPECT_NO_THROW(testBattle.runBattle());
    EXPECT_TRUE(testBattle.getBattleOutcome() == WIN);
}

TEST(BattleManagerTests, TestFixtureGetBattleOutcomeDeath)
{
    Player* player = new Player("glass cannon",HUMAN,ROGUE,1,1000); //high sp so only can cast heal
    Character enemy = Character("ImpossibletoBeat",GOBLIN,ENEMY,5000,5000,500,90);
    std::istringstream iss;
    std::ostringstream oss;
    IOManager ioManager(iss,oss);
    BattleManagerFixtureRunBattleTest testBattle(player, enemy,ioManager);
    testBattle.setAction(1);

    EXPECT_NO_THROW(testBattle.runBattle());
    //battle should be Death since player has 1 health and cannot deal damage, also goblin has max stats
    EXPECT_TRUE(testBattle.getBattleOutcome() == DEATH);
}