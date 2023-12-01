#include <gtest/gtest.h>

#include "SceneParser.h"

TEST(SceneParserTest, testEmpty)
{
    std::string text{""};
    SceneParser parser{std::begin(text), std::end(text), ""};
}

TEST(SceneParserTest, testBasic)
{
    std::string text{"# Name\n"
                     "This is some text\n"
                     "## Options\n"};

    SceneParser parser{std::begin(text), std::end(text), ""};

    auto const scenes = parser.parseScenes();

    ASSERT_EQ(scenes.size(), 1);
    EXPECT_EQ(scenes[0].first, "Name");
    EXPECT_EQ(scenes[0].second->getText(), "This is some text");
    EXPECT_EQ(scenes[0].second->getOptions().size(), 0);
}

TEST(SceneParserTest, testOptions)
{

    std::string text{"# Name\n"
                     "## Options\n"
                     " - Option 1 -> #option1\n"
                     " - Option 2 -> #option2"};

    SceneParser parser{std::begin(text), std::end(text), "test"};

    auto const scenes = parser.parseScenes();

    ASSERT_EQ(scenes.size(), 1);

    NarrativeScene const *scene = dynamic_cast<NarrativeScene const *>(scenes[0].second.get());

    ASSERT_NE(scene, nullptr);
    ASSERT_EQ(scene->getOptions().size(), 2);
    EXPECT_EQ(scene->getOptions()[0], "Option 1");
    EXPECT_EQ(scene->getNextKey(0), "test#option1");
    EXPECT_EQ(scene->getOptions()[1], "Option 2");
    EXPECT_EQ(scene->getNextKey(1), "test#option2");
}

TEST(SceneParserTest, testMultipleScenes)
{
    std::string text{"# Name\n"
                     "## Options\n"
                     " - Option 1 -> #option1\n"
                     " - Option 2 -> #option2\n"
                     "\n"
                     "# Name 2\n"
                     "## Options\n"
                     " - Option 1 -> #option1"};

    SceneParser parser{std::begin(text), std::end(text), ""};

    auto const scenes = parser.parseScenes();

    ASSERT_EQ(scenes.size(), 2);
    EXPECT_EQ(scenes[0].first, "Name");
    ASSERT_EQ(scenes[0].second->getOptions().size(), 2);
    EXPECT_EQ(scenes[0].second->getOptions()[0], "Option 1");
    EXPECT_EQ(scenes[0].second->getOptions()[1], "Option 2");

    EXPECT_EQ(scenes[1].first, "Name 2");
    ASSERT_EQ(scenes[1].second->getOptions().size(), 1);
    EXPECT_EQ(scenes[1].second->getOptions()[0], "Option 1");
}

TEST(SceneParserTest, testBattleScene)
{
    std::string text{"# [battle] Fight\n"
                     "## Enemy\n"
                     " - Bear\n"
                     "## Next\n"
                     " - #next"};

    SceneParser parser{std::begin(text), std::end(text), "test"};

    auto const scenes = parser.parseScenes();

    ASSERT_EQ(scenes.size(), 1);
    EXPECT_EQ(scenes[0].first, "Fight");

    BattleScene const *scene = dynamic_cast<BattleScene const *>(scenes[0].second.get());

    ASSERT_NE(scene, nullptr);
    EXPECT_EQ(scene->getEnemyName(), "Bear");
    EXPECT_EQ(scene->getNextKey(), "test#next");
}