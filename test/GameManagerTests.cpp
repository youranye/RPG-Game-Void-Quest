#include "CharacterManager.h"
#include "GameManager.h"
#include "IOManager.h"
#include "SceneManager.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{

class SceneStoreStub : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes{};

  public:
    SceneStoreStub()
    {
        scenes.insert({"start#Start", std::make_unique<NarrativeScene>(
                                          "End", std::vector<NarrativeScene::Option>{{"Go to End", "start#end"}})});
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
    }

    void fakeInitialize()
    {
        this->player = new Player{"DEV_PLAYER", SpeciesType::HUMAN, ClassType::ROGUE, 1, 0};
    }

    MOCK_METHOD(void, initialize, (), (override));
};

} // namespace

class GameManagerTest : public testing::Test
{
  public:
    std::istringstream iss;
    std::ostringstream oss;
    IOManager io{iss, oss};
    CharacterManagerMock characterManager{io, nullptr};
    SceneManager sceneManager{make_unique<SceneStoreStub>(), io, characterManager};
    GameManager gameManager{io, characterManager, sceneManager};
};

TEST_F(GameManagerTest, TestQuitFromStartPage)
{
    iss.str("c\n");
    gameManager.startGame();
}

TEST_F(GameManagerTest, TestCreditsFromStartPage)
{
    iss.str("b\n" // Credits
            "a\n" // Back to start
            "c\n" // Quit
    );
    gameManager.startGame();
}

TEST_F(GameManagerTest, TestGameLoop)
{
    EXPECT_CALL(characterManager, initialize()).WillOnce([this]() { this->characterManager.fakeInitialize(); });

    iss.str("a\n" // Start game
                  // Character initialization
            "a\n" // Back to start
            "c\n" // Quit
    );

    gameManager.startGame();
}