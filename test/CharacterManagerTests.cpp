#include "gtest/gtest.h"
#include "../include/CharacterManager.h"
#include "IOManager.h"

TEST(CharacterManagerTests, testConstructor)
{
    IOManager ioManager(std::cin, std::cout);
    EXPECT_NO_THROW(CharacterManager cManager(ioManager));
}

TEST(CharacterManagerTests, testGetCharacter)
{
    IOManager ioManager(std::cin, std::cout);
    CharacterManager cManager(ioManager);
    Character& nCharacter = nullCharacter;
    EXPECT_EQ(cManager.getCharacter("null"), nCharacter);
}