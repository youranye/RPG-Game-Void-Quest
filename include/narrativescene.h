#pragma once
#ifndef NARRATIVESCENE_HPP
#define NARRATIVESCENE_HPP

#include "scene.h"

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

    std::string get_text() const override
    {
        return text;
    }

    std::vector<std::string> get_options() const override
    {
        std::vector<std::string> result;
        for (auto const &option : options)
        {
            result.push_back(option.text);
        }
        return result;
    }

    std::string getKey(std::string const &optionText) const
    {
        for (auto const &option : options)
        {
            if (option.text == optionText)
            {
                return option.nextKey;
            }
        }
        throw std::invalid_argument{optionText + " is not an option"};
    }

  private:
    std::string text;
    std::vector<Option> options;
};

#endif