#pragma once
#ifndef FILESCENESTORE_H
#define FILESCENESTORE_H

#include <map>
#include <memory>
#include <string>

#include "scenestore.h"

/// @brief Scene repository based on resource files
class FileSceneStore : public SceneStore
{
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes;
    std::string const root;

    /// @brief Load scenes from a file into `scenes`
    /// @param file Filepath to load relative to `root`
    void loadFile(std::string const file);

  public:
    FileSceneStore(std::string const root) : root{root}
    {
    }

    Scene &getScene(std::string_view const) override;
};

#endif