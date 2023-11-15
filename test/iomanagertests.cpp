#include <gtest/gtest.h>

#include <sstream>

#include "iomanager.h"

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
    auto const result = manager.readOption(3);

    EXPECT_EQ(result, 1);
}

TEST_F(IOManagerTest, testPromptInputNotAChoiceRetries)
{
    iss.str("d\nb\n");
    auto const result = manager.readOption(3);

    EXPECT_EQ(oss.str(), "Please enter a letter from a to c\n");

    EXPECT_EQ(result, 1);
}

TEST_F(IOManagerTest, testPromptInputBlankRetries)
{
    iss.str("\nb\n");
    auto const result = manager.readOption(3);

    EXPECT_EQ(oss.str(), "Please enter a letter from a to c\n");

    EXPECT_EQ(result, 1);
}
