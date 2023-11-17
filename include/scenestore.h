#pragma once
#ifndef SCENESTORE_H
#define SCENESTORE_H

#include <exception>
#include <filesystem>
#include <map>
#include <memory>
#include <string_view>

#include "scene.h"

class SceneNotFoundException : public std::exception
{
    std::string message;

  public:
    SceneNotFoundException(std::string_view const key)
    {
        message.append("Scene not found: ").append(key);
    }

    char const *what() const noexcept override
    {
        return message.c_str();
    }
};

class SceneStore
{
  public:
    virtual ~SceneStore() = default;

    /// @brief Get a scene by a key
    /// @param key The key of the scene
    /// @return A reference to the Scene
    /// @throws SceneNotFoundException
    virtual Scene &getScene(std::string_view const key) = 0;
};

#endif