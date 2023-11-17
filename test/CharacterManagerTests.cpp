#include "gtest/gtest.h"
#include "../include/CharacterManager.h"

TEST(CharacterManagerTests, testConstructor)
{
    EXPECT_NO_THROW(CharacterManager());
}

TEST(CharacterManagerTests, testGetCharacter)
{
    CharacterManager cManager;
    Character& nCharacter = nullCharacter;
    EXPECT_EQ(cManager.get_character("null"), nCharacter);
}