#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "NarrativeScene.h"
#include "SceneManager.h"

class SceneStoreStub : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes{};

  public:
    SceneStoreStub()
    {
        scenes.insert({"scene1", std::make_unique<NarrativeScene>(
                                     "Scene 1", std::vector<NarrativeScene::Option>{{"Go to scene 2", "scene2"}})});
        scenes.insert({"scene2", std::make_unique<NarrativeScene>(
                                     "Scene 2", std::vector<NarrativeScene::Option>{{"Go to sceneBattle", "sceneBattle"}})});
        scenes.insert({"sceneBattle", std::make_unique<BattleScene>(
                                     "Barry the Goblin", "scene1" )});
    }

    Scene &getScene(std::string_view const key) override
    {
        if (auto it = scenes.find(key); it != std::end(scenes))
        {
            return *(it->second);
        }
        else
        {
            throw SceneNotFoundException{key};
        }
    }
};

class SceneManagerTest : public testing::Test
{
  protected:
    std::stringstream is{};
    std::stringstream os{};
    IOManager ioManager{is, os};
    CharacterManager characterManager{ioManager};
    SceneManager manager{std::make_unique<SceneStoreStub>(), ioManager, characterManager};
};

TEST_F(SceneManagerTest, testInitialSceneIsNull)
{
    EXPECT_EQ(manager.getCurrentScene(), nullptr);
}

TEST_F(SceneManagerTest, testReplaceScene)
{
    manager.replaceScene("scene1");

    EXPECT_EQ(manager.getCurrentScene()->getText(), "Scene 1");
}

TEST_F(SceneManagerTest, testReplaceWithMissingSceneThrowsSceneNotFoundException)
{
    manager.replaceScene("scene1");
    Scene * scene = manager.getCurrentScene();

    EXPECT_THROW(manager.replaceScene("scene0"), SceneNotFoundException);

    // Assert that the scene is unchanged
    EXPECT_EQ(manager.getCurrentScene(), scene);
}

TEST_F(SceneManagerTest, testRunNarrativeScene)
{
    is.str("a\n");
    manager.replaceScene("scene2");
    Scene* nextScene = manager.getCurrentScene(); // this is the scene after scene1

    manager.replaceScene("scene1");
    manager.runScene();
    
    EXPECT_EQ(manager.getCurrentScene(), nextScene);
}

/*
TEST_F(SceneManagerTest, testRunBattleScene)
{
    is.str("b\n b\n b\n b\n b\n b\n b\n b\n b\n"); // heal until
    manager.replaceScene("scene1");
    Scene* nextScene = manager.getCurrentScene(); // this is the scene after sceneBattle

    manager.replaceScene("sceneBattle");
    manager.runScene();
    
    EXPECT_EQ(manager.getCurrentScene(), nextScene);
}
*/