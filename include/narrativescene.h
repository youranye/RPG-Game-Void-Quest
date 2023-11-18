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

    void accept(SceneVisitor &visitor)
    {
        visitor.visit(*this);
    }

    std::string get_text() const override
    {
        return text;
    }

    std::vector<std::string> get_options() const override;

    std::string getKey(std::string const &optionText) const;

  private:
    std::string text;
    std::vector<Option> options;
};

#endif