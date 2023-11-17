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
                     " - Option 1 -> #option1\n"
                     " - Option 2 -> #option2"};

    SceneParser parser{std::begin(text), std::end(text)};

    auto const scenes = parser.parse_scenes();

    ASSERT_EQ(scenes.size(), 1);

    if (NarrativeScene const *scene = dynamic_cast<NarrativeScene const*>(scenes[0].second.get()); scene != nullptr)
    {
        ASSERT_EQ(scene->get_options().size(), 2);
        EXPECT_EQ(scene->get_options()[0], "Option 1");
        EXPECT_EQ(scene->getKey("Option 1"), "#option1");
        EXPECT_EQ(scene->get_options()[1], "Option 2");
        EXPECT_EQ(scene->getKey("Option 2"), "#option2");
    }
    else
    {
        FAIL();
    }
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

    SceneParser parser{std::begin(text), std::end(text)};

    auto const scenes = parser.parse_scenes();

    ASSERT_EQ(scenes.size(), 2);
    EXPECT_EQ(scenes[0].first, "Name");
    ASSERT_EQ(scenes[0].second->get_options().size(), 2);
    EXPECT_EQ(scenes[0].second->get_options()[0], "Option 1");
    EXPECT_EQ(scenes[0].second->get_options()[1], "Option 2");

    EXPECT_EQ(scenes[1].first, "Name 2");
    ASSERT_EQ(scenes[1].second->get_options().size(), 1);
    EXPECT_EQ(scenes[1].second->get_options()[0], "Option 1");
}