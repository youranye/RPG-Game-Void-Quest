#pragma once
#ifndef FILESCENESTORE_H
#define FILESCENESTORE_H

#include "scenestore.h"

class FileSceneStore : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes;
    std::filesystem::path const root;

    void load_file(std::filesystem::path const);

  public:
    FileSceneStore(std::filesystem::path const root) : root{root}
    {
    }

    Scene &getScene(std::string_view const) override;
};

#endif