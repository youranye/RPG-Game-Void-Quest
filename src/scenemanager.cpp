#include "scenemanager.h"

void SceneManager::replaceScene(std::string const &key)
{
    currentScene = &(store->getScene(key));
}