#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "narrativescene.h"
#include "scenemanager.h"

class SceneStoreStub : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes{};

  public:
    SceneStoreStub()
    {
        scenes.insert({"scene1", std::make_unique<NarrativeScene>("Scene 1", std::vector<std::string>{"scene2"})});
        scenes.insert({"scene2", std::make_unique<NarrativeScene>("Scene 2", std::vector<std::string>{"scene3"})});
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
    SceneManager manager{std::make_unique<SceneStoreStub>()};
};

TEST_F(SceneManagerTest, testInitialSceneIsNull)
{
    EXPECT_EQ(manager.getCurrentScene(), nullptr);
}

TEST_F(SceneManagerTest, testReplaceScene)
{
    manager.replaceScene("scene1");

    EXPECT_EQ(manager.getCurrentScene()->get_text(), "Scene 1");
}

TEST_F(SceneManagerTest, testReplaceWithMissingSceneThrowsSceneNotFoundException)
{
    manager.replaceScene("scene1");
    Scene * scene = manager.getCurrentScene();

    EXPECT_THROW(manager.replaceScene("scene0"), SceneNotFoundException);

    // Assert that the scene is unchanged
    EXPECT_EQ(manager.getCurrentScene(), scene);
}