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