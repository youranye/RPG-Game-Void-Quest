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

    Scene *getCurrentScene()
    {
        return currentScene;
    }

    void replaceScene(std::string const &key);
};

#endif