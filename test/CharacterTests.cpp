#include "gtest/gtest.h"
#include "../include/Character.h"

class CharacterFixture : public Character {
    public:
    CharacterFixture() : Character() {}
};
TEST(CharacterTest, TestConstructor)
{
    EXPECT_NO_THROW(CharacterFixture());
    EXPECT_NO_THROW(Character("Name", VOIDWALKER, STORY, 2));
}

TEST(CharacterTest, testConstructorDeaths)
{
    EXPECT_THROW(Character("", VOIDWALKER, STORY, 2),std::invalid_argument);
    EXPECT_THROW(Character("name", VOIDWALKER, STORY, 0),std::invalid_argument);
}