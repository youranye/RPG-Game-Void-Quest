#include <gtest/gtest.h>

#include <sstream>

#include "iomanager.hpp"

class IOManagerTest : public testing::Test
{
  protected:
    std::istringstream iss;
    std::ostringstream oss;

    IOManager manager{iss, oss};
};

TEST_F(IOManagerTest, testWrite)
{
    manager.write("Hello, World!");

    EXPECT_EQ(oss.str(), "Hello, World!");
}

TEST_F(IOManagerTest, testPrompt)
{
    iss.str("b\n");
    auto const result = manager.prompt({"option 1", "option 2", "option 3"});

    EXPECT_EQ(result, "option 2");
}

TEST_F(IOManagerTest, testPromptInputNotAChoiceRetries)
{
    iss.str("d\nb\n");
    auto const result = manager.prompt({"option 1", "option 2", "option 3"});

    EXPECT_EQ(oss.str(), "a. option 1\n"
                         "b. option 2\n"
                         "c. option 3\n"
                         "Please enter a letter from a to c\n");

    EXPECT_EQ(result, "option 2");
}

TEST_F(IOManagerTest, testPromptInputBlankRetries)
{
    iss.str("\nb\n");
    auto const result = manager.prompt({"option 1", "option 2", "option 3"});

    EXPECT_EQ(oss.str(), "a. option 1\n"
                         "b. option 2\n"
                         "c. option 3\n"
                         "Please enter a letter from a to c\n");

    EXPECT_EQ(result, "option 2");
}
