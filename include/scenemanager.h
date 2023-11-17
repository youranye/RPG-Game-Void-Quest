#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>

#include "scenestore.h"

class SceneManager
{
  private:
    std::unique_ptr<SceneStore> store;
    Scene *currentScene;

  public:
    SceneManager(std::unique_ptr<SceneStore> store) : store{std::move(store)}, currentScene{nullptr}
    {
    }

    /// @brief Return a pointer to the current scene
    /// @return A pointer to the current scene
    Scene *getCurrentScene()
    {
        return currentScene;
    }

    /// @brief Replace the current scene with the scene identified by key
    /// @param key Key of the scene to replace with
    /// @throws `SceneNotFoundException`
    void replaceScene(std::string const &key);
};

#endif