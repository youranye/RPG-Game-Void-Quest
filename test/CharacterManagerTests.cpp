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

// TEST_F(CharacterManagerCreatePlayerTest, CreatesValidPlayerCharacter) 
// {
//     // Mock user input for the test
//     // Replace these input lines with the actual simulated user input for species and class selection
//     std::istringstream simulatedInput("b\na\nJohn\n");
//     ioManager = IOManager(simulatedInput, std::cout);
//     characterManager = CharacterManager(ioManager);

//     Player* player = characterManager.createPlayer();
//     ASSERT_NE(player, nullptr); // Check if the player character is created successfully

//     EXPECT_EQ(player->getName(), "John"); // Replace "John" with the expected name
//     EXPECT_EQ(player->getSpecies(), ELF); // Replace ELF with the expected species
//     EXPECT_EQ(player->getClass(), ROGUE); // Replace ROGUE with the expected class
// }

TEST(CharacterManagerTests, testInitializeMultipleTimes)
{
    std::stringstream mockUser;
    std::stringstream junkOutput;
    mockUser << "b" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    mockUser << "b" << std::endl << "b" << std::endl << "Elven Paladin" << std::endl;
    IOManager ioManager(mockUser, junkOutput);
    CharacterManager myCharacters(ioManager);
    myCharacters.initialize();
    
    EXPECT_THROW(myCharacters.initialize(), std::logic_error);
}

// TEST(CharacterManagerTests, testInitializeAgain)
// {
//     std::stringstream mockUser;
//     std::stringstream junkOutput;
//     mockUser << "a" << std::endl << "a" << std::endl << "Elven Paladin" << std::endl;
//     IOManager ioManager(mockUser, junkOutput);
//     CharacterManager myCharacters(ioManager);
//     myCharacters.initialize();
//     Character& character = myCharacters.getCharacter("Elven Paladin");
//     character.takeDamage(10000);
//     mockUser << "a" << std::endl << "a" << std::endl << "Elven Paladin" << std::endl;
    
    
//     EXPECT_NO_THROW(myCharacters.initialize());
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