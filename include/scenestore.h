#pragma once
#ifndef SCENESTORE_HPP
#define SCENESTORE_HPP

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
    std::map<std::string, std::unique_ptr<Scene>, std::less<>> scenes;
    std::filesystem::path const root;

    void load_file(std::filesystem::path const);

  public:
    SceneStore(std::filesystem::path const root) : root{root}
    {
    }

    Scene &get_scene(std::string_view const);
};

#endif