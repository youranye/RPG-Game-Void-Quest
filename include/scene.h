#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

class Scene
{
  public:
    virtual ~Scene() = default;

    virtual std::string get_text() = 0;
    virtual std::vector<std::string> get_options() = 0;
};

#endif