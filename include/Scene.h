#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

class Scene
{
  public:
    virtual ~Scene() = default;

    /// @brief Get the text of the scene
    /// @return The text of the scene
    virtual std::string getText() const = 0;

    /// @brief Get the options for the scene
    /// @return A vector of the names of each option
    virtual std::vector<std::string> getOptions() const = 0;
};

#endif