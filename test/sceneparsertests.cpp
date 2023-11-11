#include <gtest/gtest.h>

#include "narrativescene.h"
#include "sceneparser.h"

TEST(SceneParserTest, testEmpty)
{
    std::string text{""};
    SceneParser parser{std::begin(text), std::end(text)};
}

TEST(SceneParserTest, testBasic)
{
    std::string text{"# Name\n"
                     "This is some text\n"
                     "## Options\n"};

    SceneParser parser{std::begin(text), std::end(text)};

    auto const scenes = parser.parse_scenes();

    ASSERT_EQ(scenes.size(), 1);
    EXPECT_EQ(scenes[0].first, "Name");
    EXPECT_EQ(scenes[0].second->get_text(), "This is some text");
    EXPECT_EQ(scenes[0].second->get_options().size(), 0);
}

TEST(SceneParserTest, testOptions)
{

    std::string text{"# Name\n"
                     "## Options\n"
                     " - Option 1\n"
                     " - Option 2"};

    SceneParser parser{std::begin(text), std::end(text)};

    auto const scenes = parser.parse_scenes();

    ASSERT_EQ(scenes.size(), 1);
    ASSERT_EQ(scenes[0].second->get_options().size(), 2);
    EXPECT_EQ(scenes[0].second->get_options()[0], "Option 1");
    EXPECT_EQ(scenes[0].second->get_options()[1], "Option 2");
}