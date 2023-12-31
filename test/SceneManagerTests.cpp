#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <streambuf>

#include "NarrativeScene.h"
#include "SceneManager.h"

namespace
{

class SceneStoreStub : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes{};

  public:
    SceneStoreStub()
    {
        scenes.insert({"scene1", std::make_unique<NarrativeScene>(
                                     "Scene 1", std::vector<NarrativeScene::Option>{{"Go to scene 2", "scene2"}})});
        scenes.insert(
            {"scene2", std::make_unique<NarrativeScene>(
                           "Scene 2", std::vector<NarrativeScene::Option>{{"Go to sceneBattle", "sceneBattle"}})});
        scenes.insert({"sceneBattleWin", std::make_unique<BattleScene>("dead meat", "scene1")});
        scenes.insert({"sceneBattleLose", std::make_unique<BattleScene>("overpowered meat", "scene1")});
        scenes.insert({"sceneBattleEmpty", std::make_unique<BattleScene>("missing meat", "scene1")});
        scenes.insert({"sceneBattleBoss", std::make_unique<BattleScene>("big boss", "scene1")});
        scenes.insert({"scene3", std::make_unique<NarrativeScene>(
                                     "Scene 3", std::vector<NarrativeScene::Option>{{"Go to scene 4", "scene4"}})});
        scenes.insert({"scene4", std::make_unique<NarrativeScene>(
                                     "Scene 4", std::vector<NarrativeScene::Option>{{"Go to End", "start#end"}})});
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

class CharacterManagerMock : public CharacterManager
{
  public:
    CharacterManagerMock(IOManager &io, Player *player) : CharacterManager{io}
    {
        this->player = player;
        this->characters.emplace_back("dead meat", SpeciesType::VOIDWALKER, CharacterType::ENEMY, 1, 0, 0, 0);
        this->characters.emplace_back("overpowered meat", SpeciesType::VOIDWALKER, CharacterType::ENEMY, 999'999,
                                      999'999, 999'999, 999'999);
        this->characters.emplace_back("big boss", SpeciesType::VOIDWALKER, CharacterType::BOSS, 1, 0, 0, 0);

        ON_CALL(*this, initialize()).WillByDefault([this]() { this->fakeInitialize(); });
    }

    void fakeInitialize()
    {
        this->player = new Player{"DEV_PLAYER", SpeciesType::HUMAN, ClassType::ROGUE, 1, 0};
    }

    MOCK_METHOD(void, initialize, (), (override));
};

} // namespace

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
    Scene *scene = manager.getCurrentScene();

    EXPECT_THROW(manager.replaceScene("scene0"), SceneNotFoundException);

    // Assert that the scene is unchanged
    EXPECT_EQ(manager.getCurrentScene(), scene);
}

TEST_F(SceneManagerTest, testRunNarrativeScene)
{
    is.str("a\na\n");
    manager.replaceScene("scene4");
    Scene *nextScene = manager.getCurrentScene(); // this is the scene after scene1

    manager.replaceScene("scene3");
    manager.runScene();
    EXPECT_EQ(manager.getCurrentScene(), nextScene);
}

class loopinputbuf : public std::streambuf
{
    inline static char buffer[] = {'a', '\n'};

  public:
    int underflow() override
    {
        setg(buffer, buffer, buffer + sizeof(buffer) / sizeof(*buffer));
        return buffer[0];
    }
};

TEST_F(SceneManagerTest, testRunBattleSceneWin)
{
    loopinputbuf generatorbuf{};
    std::istream is{&generatorbuf};
    std::stringstream os{};
    IOManager ioManager{is, os};
    CharacterManagerMock characterManager{ioManager,
                                          new Player{"DEV_PLAYER", SpeciesType::HUMAN, ClassType::ROGUE, 999'999, 0}};

    SceneManager manager{std::make_unique<SceneStoreStub>(), ioManager, characterManager};

    manager.replaceScene("scene1");
    Scene *nextScene = manager.getCurrentScene(); // this is the scene after sceneBattle

    manager.replaceScene("sceneBattleWin");
    manager.runScene();

    EXPECT_EQ(manager.getCurrentScene(), nextScene);
}

TEST_F(SceneManagerTest, testRunBattleSceneLose)
{
    loopinputbuf generatorbuf{};
    std::istream is{&generatorbuf};
    std::stringstream os{};
    IOManager ioManager{is, os};
    CharacterManagerMock characterManager{ioManager,
                                          new Player{"DEV_PLAYER", SpeciesType::HUMAN, ClassType::ROGUE, 1, 0}};

    SceneManager manager{std::make_unique<SceneStoreStub>(), ioManager, characterManager};

    manager.replaceScene("sceneBattleLose");
    manager.runScene();

    EXPECT_EQ(manager.getCurrentScene(), nullptr);
}

TEST_F(SceneManagerTest, testRunBattleSceneBoss)
{
    loopinputbuf generatorbuf{};
    std::istream is{&generatorbuf};
    std::stringstream os{};
    IOManager ioManager{is, os};
    CharacterManagerMock characterManager{ioManager,
                                          new Player{"DEV_PLAYER", SpeciesType::HUMAN, ClassType::ROGUE, 1, 0}};

    SceneManager manager{std::make_unique<SceneStoreStub>(), ioManager, characterManager};

    manager.replaceScene("sceneBattleBoss");
    manager.runScene();
}

TEST_F(SceneManagerTest, testRunNullScene)
{
    assert(manager.getCurrentScene() == nullptr);
    manager.runScene();
    ASSERT_EQ(manager.getCurrentScene(), nullptr);
}

TEST_F(SceneManagerTest, testBattleSceneNoEnemy)
{
    manager.replaceScene("scene1");
    Scene *nextScene = manager.getCurrentScene(); // this is the scene after sceneBattle

    manager.replaceScene("sceneBattleEmpty");
    manager.runScene();

    ASSERT_EQ(manager.getCurrentScene(), nextScene);
}

TEST_F(SceneManagerTest, testRunSceneWithoutPlayerCausesInitialization)
{
    using ::testing::Return;

    std::istringstream is{};
    std::ostringstream os{};
    IOManager ioManager{is, os};
    CharacterManagerMock characterManager{ioManager, nullptr};
    SceneManager manager{std::make_unique<SceneStoreStub>(), ioManager, characterManager};
    manager.replaceScene("sceneBattleLose");

    EXPECT_CALL(characterManager, initialize());

    manager.runScene();
}