#include "gtest/gtest.h"
#include "../include/Character.h"

class CharacterFixture : public Character {
    public:
    CharacterFixture() : Character() {}
};
TEST(CharacterTest, TestConstructor)
{
    EXPECT_NO_THROW(CharacterFixture());
    EXPECT_NO_THROW(Character("Name", VOIDWALKER, STORY, 2, 0, 0, 0));
}

TEST(CharacterTest, testConstructorDeaths)
{
    EXPECT_THROW(Character("", VOIDWALKER, STORY, 2, 0, 0, 0),std::invalid_argument);
    EXPECT_THROW(Character("name", VOIDWALKER, STORY, 0, 0, 0, 0),std::invalid_argument);
}

// There are 2 kinds of characters (with or without ability attribute)
// 'Ab' means testing on the character which has the attribute 'ability' 
// Test getName() function
TEST(CharacterTest, GetName) 
{
    Character character("Alice", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40);
    EXPECT_EQ(character.getName(), "Alice");
}

TEST(CharacterTest, GetNameAb) 
{
    Character character("Alice", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_EQ(character.getName(), "Alice");
}

// Test getSpecies() function
TEST(CharacterTest, GetSpecies) 
{
    Character character("Bob", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40);
    EXPECT_EQ(character.getSpecies(), SpeciesType::ELF);
}

TEST(CharacterTest, GetSpeciesAb) 
{
    Character character("Bob", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_EQ(character.getSpecies(), SpeciesType::ELF);
}

// Test getType() function
TEST(CharacterTest, GetType) 
{
    Character character("Charlie", SpeciesType::ORC, CharacterType::PLAYER,10,20,30,40);
    EXPECT_EQ(character.getType(), CharacterType::PLAYER);
}

TEST(CharacterTest, GetTypeAb) 
{
    Character character("Charlie", SpeciesType::ORC, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_EQ(character.getType(), CharacterType::PLAYER);
}

// Test getAttack(), getDefense(), getDexterity() functions
TEST(CharacterTest, GetStats) 
{
    Character character("Dave", SpeciesType::DWARF, CharacterType::PLAYER,10,20,30,40);
    EXPECT_EQ(character.getAttack(), 20);
    EXPECT_EQ(character.getDefense(), 30);
    EXPECT_EQ(character.getDexterity(), 40);
}

TEST(CharacterTest, GetStatsAb) 
{
    Character character("Dave", SpeciesType::DWARF, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_EQ(character.getAttack(), 20);
    EXPECT_EQ(character.getDefense(), 30);
    EXPECT_EQ(character.getDexterity(), 40);
}

// Test heal() function
TEST(CharacterTest, Heal) 
{
    Character character("Eve", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40);
    character.takeDamage(20);
    character.heal(10);
    EXPECT_EQ(character.getHP(), 10);
}

TEST(CharacterTest, HealAb) 
{
    Character character("Eve", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    character.takeDamage(20);
    character.heal(10);
    EXPECT_EQ(character.getHP(), 10);
}

// Test takeDamage() function
TEST(CharacterTest, TakeDamage) 
{
    Character character("Fiona", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40);
    character.takeDamage(30);
    EXPECT_EQ(character.getHP(), 0);
}

TEST(CharacterTest, TakeDamageAb) 
{
    Character character("Fiona", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    character.takeDamage(30);
    EXPECT_EQ(character.getHP(), 0);
}

// Test getMaxHP() function
TEST(CharacterTest, GetMaxHP) 
{
    Character character("Gina", SpeciesType::ORC, CharacterType::PLAYER,10,20,30,40);
    EXPECT_EQ(character.getMaxHP(), 10);
}

TEST(CharacterTest, GetMaxHPAb) 
{
    Character character("Gina", SpeciesType::ORC, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_EQ(character.getMaxHP(), 10);
}

// Test getAbility() function
TEST(CharacterTest, GetAbility) 
{
    Character character("Harry", SpeciesType::DWARF, CharacterType::PLAYER,10,20,30,40);
    EXPECT_EQ(character.getAbility().name, "InvalidAbility");
}
 
TEST(CharacterTest, GetAbilityAb) 
{
    Ability abil = Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 1);
    Character character("Harry", SpeciesType::DWARF, CharacterType::ENEMY,10,20,30,40, abil);
    EXPECT_EQ(abil.name, "Basic Attack");
    EXPECT_EQ(character.getAbility().name, abil.name);
}

// Test getHPBar() function
TEST(CharacterTest, GetHPBarDamageMoreThanHP) 
{
    Character character("Ivy", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40);
    character.takeDamage(25); 
    EXPECT_EQ(character.getHPBar(), "[  ]"); 
}

TEST(CharacterTest, GetHPBarDamageMoreThanHPAb) 
{
    Character character("Ivy", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    character.takeDamage(25); 
    EXPECT_EQ(character.getHPBar(), "[  ]"); 
}

TEST(CharacterTest, GetHPBar) 
{
    Character character("Ivy", SpeciesType::HUMAN, CharacterType::PLAYER,50,20,30,40);
    character.takeDamage(25); 
    EXPECT_EQ(character.getHPBar(), "[\033[38:5:202m:::::\033[1;0m     ]"); 
}

TEST(CharacterTest, GetHPBarAb) 
{
    Character character("Ivy", SpeciesType::HUMAN, CharacterType::PLAYER,50,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    character.takeDamage(25); 
    EXPECT_EQ(character.getHPBar(), "[\033[38:5:202m:::::\033[1;0m     ]"); 
}

// Test operator== function
TEST(CharacterTest, OperatorEquals) {
    Character character1("Jack", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40);
    Character character2("Jack", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40);
    EXPECT_TRUE(character1 == character2);
    Character character3("John", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40);
    EXPECT_FALSE(character1 == character3);
}

TEST(CharacterTest, OperatorEqualsAb) {
    Character character1("Jack", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    Character character2("Jack", SpeciesType::ELF, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_TRUE(character1 == character2);
    Character character3("John", SpeciesType::HUMAN, CharacterType::PLAYER,10,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    EXPECT_FALSE(character1 == character3);
}

TEST(CharacterTest, HealHpDownByOne) 
{
    Character character("Ivy", SpeciesType::HUMAN, CharacterType::PLAYER,50,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    character.takeDamage(1); 
    character.heal(100);
    EXPECT_EQ(character.getHP(),50); 
}

TEST(CharacterTest, HPBarGreaterThan1000) 
{
    Character character("Ivy", SpeciesType::HUMAN, CharacterType::PLAYER,1500,20,30,40, 
    Ability("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0));
    //one hundred dots with the coloring string attachments
    EXPECT_EQ(character.getHPBar(),"[\x1B[1;32m::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\x1B[1;0m]"); 
}