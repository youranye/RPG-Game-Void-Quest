#pragma once
#ifndef NARRATIVESCENE_HPP
#define NARRATIVESCENE_HPP

#include "scene.h"

class NarrativeScene : public Scene
{
    std::string text;
    std::vector<std::string> options;

  public:
    NarrativeScene(std::string_view const text, std::vector<std::string> const &options) : text{text}, options{options}
    {
    }

    std::string get_text() override
    {
        return text;
    }
    std::vector<std::string> get_options() override
    {
        return options;
    }
};

#endif