#include "gtest/gtest.h"
#include "GameManager.h"
#include "IOManager.h" // Assuming you have an IOManager class

TEST(StartGame, TestStartGame)
{
    std::istringstream iss;
    std::ostringstream oss;
    IOManager manager{iss, oss};
    GameManager gm(manager);
    iss.str("a\n");
    EXPECT_NO_THROW(gm.startGame());
}


// TEST(DisplayStartPage, TestDisplayStartPage)
// {
//     IOManager mockIOManager{iss, oss};
//     GameManager gm(mockIOManager);
//     std::string expectedOutput =
//         "===== Void Quest =====\n"
//         "Welcome to Void Quest, a text-based fantasy RPG! To play, enter the letter of the option you want to choose. \n"
//         "a) Start game\n"
//         "b) View credits.\n";
//     EXPECT_EQ(expectedOutput,gm.startGame());
// }
