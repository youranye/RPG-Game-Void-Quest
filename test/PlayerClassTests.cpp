#include "gtest/gtest.h"
#include "Player.h"

TEST(PlayerTest, TestConstructor)
{
    EXPECT_NO_THROW(Player("Elrond",HUMAN,ROGUE,100,100));
    EXPECT_NO_THROW(Player("Elrond",HUMAN,PALADIN,100,100));
    EXPECT_NO_THROW(Player("Elrond",HUMAN,WARLOCK,100,100));
    EXPECT_NO_THROW(Player("Elrond",DWARF,FORGED,100,100));
}

TEST(PlayerTest, testConstructorDeaths)
{
    EXPECT_THROW(Player("Elrond",HUMAN,ROGUE,-1,-1),std::invalid_argument);
    EXPECT_THROW(Player("Elrond",HUMAN,ROGUE,0,0),std::invalid_argument);
    EXPECT_THROW(Player("Elrond",HUMAN,ROGUE,1,-1),std::invalid_argument);
}

TEST(PlayerTest, testConstructorRogue)
{
    Player Elrond("Elrond",HUMAN,ROGUE,100,100);
    EXPECT_EQ(Elrond.getAttack(),25);
    EXPECT_EQ(Elrond.getDefense(),15);
    EXPECT_EQ(Elrond.getDexterity(),20);
}

TEST(PlayerTest, testConstructorPaladin)
{
    Player Elrond("Elrond",HUMAN,PALADIN,100,100);
    EXPECT_EQ(Elrond.getAttack(),20);
    EXPECT_EQ(Elrond.getDefense(),25);
    EXPECT_EQ(Elrond.getDexterity(),15);
}

TEST(PlayerTest, testConstructorWarlock)
{
    Player Elrond("Elrond",HUMAN,WARLOCK,100,100);
    EXPECT_EQ(Elrond.getAttack(),15);
    EXPECT_EQ(Elrond.getDefense(),20);
    EXPECT_EQ(Elrond.getDexterity(),25);
}

TEST(PlayerTest, testConstructorForged)
{
    Player Elrond("Elrond",DWARF,FORGED,100,100);
    EXPECT_EQ(Elrond.getAttack(),30);
    EXPECT_EQ(Elrond.getDefense(),30);
    EXPECT_EQ(Elrond.getDexterity(),10);
}

// Test getClass() method
TEST(PlayerTest, GetClass) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);
    EXPECT_EQ(player.getClass(), ClassType::ROGUE);
    // Add more assertions as needed for other classes
}

// Test getSP() method
TEST(PlayerTest, GetSP) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);
    EXPECT_EQ(player.getSP(), 100); // Initial SP
}

// Test spendSP() method
TEST(PlayerTest, SpendSP) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);

    player.spendSP(50); // Spend 50 SP
    EXPECT_EQ(player.getSP(), 50); // SP after spending

    player.spendSP(1000); // Spend more than available SP
    EXPECT_EQ(player.getSP(), 0); // SP should be zero
}

// Test regenerateSP() method
TEST(PlayerTest, RegenerateSP) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);

    player.regenerateSP(50); // Regenerate more than the maximum SP
    EXPECT_EQ(player.getSP(), 100); // SP should not exceed the maximum value
}

TEST(PlayerTest, SPManipulation) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);

    player.spendSP(50); // Spend 50 SP
    EXPECT_EQ(player.getSP(), 50); // SP after spending

    player.regenerateSP(30); // Regenerate 30 SP
    EXPECT_EQ(player.getSP(), 80); // SP after regeneration
}

TEST(PlayerTest, RegenerateMoreThanMaxSP) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);

    player.spendSP(50); // Spend 50 SP
    EXPECT_EQ(player.getSP(), 50); // SP after spending

    player.regenerateSP(30); // Regenerate 30 SP
    EXPECT_EQ(player.getSP(), 80); // SP after regeneration
    // Test SP limits

    player.regenerateSP(1000); // Regenerate more than the maximum SP
    EXPECT_EQ(player.getSP(), 100); // SP should not exceed the maximum value
}

// Test getMaxSP() method
TEST(PlayerTest, GetMaxSP) 
{
    Player player("TestPlayer", SpeciesType::HUMAN, ClassType::ROGUE, 200, 100);
    EXPECT_EQ(player.getMaxSP(), 100);
    // Add more assertions as needed for different maximum SP values
}