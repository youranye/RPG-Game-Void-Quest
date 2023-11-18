#pragma once
#ifndef FILESCENESTORE_H
#define FILESCENESTORE_H

#include "scenestore.h"

/// @brief Scene repository based on resource files
class FileSceneStore : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes;
    std::filesystem::path const root;

    /// @brief Load scenes from a file into `scenes`
    /// @param file Filepath to load relative to `root`
    void loadFile(std::filesystem::path const file);

  public:
    FileSceneStore(std::filesystem::path const root) : root{root}
    {
    }

    Scene &getScene(std::string_view const) override;
};

#endif