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
    EXPECT_EQ(Elrond.get_attack(),10);
    EXPECT_EQ(Elrond.get_defense(),10);
    EXPECT_EQ(Elrond.get_dexterity(),20);
}

TEST(PlayerTest, testConstructorPaladin)
{
    Player Elrond("Elrond",HUMAN,PALADIN,100,100);
    EXPECT_EQ(Elrond.get_attack(),9);
    EXPECT_EQ(Elrond.get_defense(),15);
    EXPECT_EQ(Elrond.get_dexterity(),10);
}

TEST(PlayerTest, testConstructorWarlock)
{
    Player Elrond("Elrond",HUMAN,WARLOCK,100,100);
    EXPECT_EQ(Elrond.get_attack(),9);
    EXPECT_EQ(Elrond.get_defense(),11);
    EXPECT_EQ(Elrond.get_dexterity(),15);
}

TEST(PlayerTest, testConstructorForged)
{
    Player Elrond("Elrond",DWARF,FORGED,100,100);
    EXPECT_EQ(Elrond.get_attack(),15);
    EXPECT_EQ(Elrond.get_defense(),15);
    EXPECT_EQ(Elrond.get_dexterity(),10);
}