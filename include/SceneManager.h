#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include "SceneStore.h"
#include "IOManager.h"
#include "CharacterManager.h"
#include "BattleManager.h"
#include "NarrativeScene.h"
#include "BattleScene.h"


class SceneManager
{
  public:
    SceneManager(std::unique_ptr<SceneStore> store, IOManager& iomanager, CharacterManager& characterManager) : store{std::move(store)}, ioManager(iomanager), characterManager(characterManager), currentScene{nullptr}
    {
    }

    /// @brief Return a pointer to the current scene
    /// @return A pointer to the current scene
    Scene *getCurrentScene()
    {
      return currentScene;
    }

    // Run the current scene. Treat it differently depending on whether it is battle or narrative.
    void runScene();

    /// @brief Replace the current scene with the scene identified by key
    /// @param key Key of the scene to replace with
    /// @throws `SceneNotFoundException`
    void replaceScene(std::string const &key);

  private:
    std::unique_ptr<SceneStore> store;
    IOManager& ioManager;
    CharacterManager& characterManager;
    Scene *currentScene;

    void handleNonBattleScene(NarrativeScene* nScene);
    void handleBattleScene(BattleScene* bScene);
};

#endif