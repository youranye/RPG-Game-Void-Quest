#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "scenevisitor.h"

class Scene
{
  public:
    virtual ~Scene() = default;

    virtual void accept(SceneVisitor &) = 0;

    /// @brief Get the text of the scene
    /// @return The text of the scene
    virtual std::string get_text() const = 0;

    /// @brief Get the options for the scene
    /// @return A vector of the names of each option
    virtual std::vector<std::string> get_options() const = 0;
};

#endif