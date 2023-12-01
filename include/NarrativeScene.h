#pragma once
#ifndef NARRATIVESCENE_HPP
#define NARRATIVESCENE_HPP

#include "Scene.h"

class NarrativeScene : public Scene
{
  public:
    struct Option
    {
        std::string text;
        std::string nextKey;
    };

    NarrativeScene(std::string_view const text, std::vector<Option> const &options) : text{text}, options{options}
    {
    }

    std::string getText() const override
    {
        return text;
    }

    std::vector<std::string> getOptions() const override;
    std::string getNextKey(int index) const;

  private:
    std::string text;
    std::vector<Option> options;
};

#endif