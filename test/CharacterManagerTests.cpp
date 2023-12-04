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

// TEST(CharacterManagerTests, testCreatePlayer)
// {
//     std::stringstream mockUser;
//     std::stringstream junkOutput;
//     mockUser << "b" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
//     IOManager ioManager(mockUser, junkOutput);
//     CharacterManager myCharacters(ioManager);
//     myCharacters.initialize();
//     Player* player = myCharacters.getPlayer();

//     EXPECT_EQ(player->getName(), "Elven Paladin");
//     EXPECT_EQ(player->getSpecies(), 1);
//     EXPECT_EQ(player->getClass(), 1);
// }

TEST(CharacterManagerTests, testInitializeElfPaladin)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "b" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 1);
    EXPECT_EQ(player->getClass(), 1);
}

TEST(CharacterManagerTests, testInitializeDwarvenForged)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "c" << std::endl << "b" << std::endl << "Dwarven Forged" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Dwarven Forged");
    EXPECT_EQ(player->getSpecies(), 2);
    EXPECT_EQ(player->getClass(), 3);
}

TEST(CharacterManagerTests, testInitializeTabaxiWarlock)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "e" << std::endl << "c" << std::endl << "Tabaxi Warlock" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Tabaxi Warlock");
    EXPECT_EQ(player->getSpecies(), 4);
    EXPECT_EQ(player->getClass(), 2);
}

// Test getSpecies
TEST(CharacterManagerTests, testInitializeHuman)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "a" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 0);
    EXPECT_EQ(player->getClass(), 1);
}

TEST(CharacterManagerTests, testInitializeElf)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "b" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 1);
    EXPECT_EQ(player->getClass(), 1);
}

TEST(CharacterManagerTests, testInitializeDwarf)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "c" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 2);
    EXPECT_EQ(player->getClass(), 3);
}

TEST(CharacterManagerTests, testInitializeGoblin)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "d" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 3);
    EXPECT_EQ(player->getClass(), 1);
}

TEST(CharacterManagerTests, testInitializeTabaxi)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "e" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 4);
    EXPECT_EQ(player->getClass(), 1);
}

// Test getClass for Dwarf
TEST(CharacterManagerTests, testInitializeDwarfRogue)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "c" << std::endl << "a" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 2);
    EXPECT_EQ(player->getClass(), 0);
}

TEST(CharacterManagerTests, testInitializeDwarfForged)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "c" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 2);
    EXPECT_EQ(player->getClass(), 3);
}

// Test getClass for non-dwarf species
TEST(CharacterManagerTests, testInitializeRogue)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "a" << std::endl << "a" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 0);
    EXPECT_EQ(player->getClass(), 0);
}

TEST(CharacterManagerTests, testInitializePaladin)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "a" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 0);
    EXPECT_EQ(player->getClass(), 1);
}

TEST(CharacterManagerTests, testInitializeWarlock)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "a" << std::endl << "c" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    Player* player = myCharacters.getPlayer();

    EXPECT_EQ(player->getName(), "Elven Paladin");
    EXPECT_EQ(player->getSpecies(), 0);
    EXPECT_EQ(player->getClass(), 2);
}