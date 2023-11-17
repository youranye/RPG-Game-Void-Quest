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
    virtual Scene &getScene(std::string_view const) = 0;
};

#endif