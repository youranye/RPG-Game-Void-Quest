#pragma once
#ifndef SCENEPARSER_HPP
#define SCENEPARSER_HPP

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "scene.h"
#include "narrativescene.h"

class SceneParseException : public std::exception
{
};

template <class It, class Se> class SceneParser
{
    enum class LineType
    {
        None,
        H1,
        H2,
        Text,
        Option,
    };

    struct Line
    {
        LineType type;
        std::string text;
    };

    It cur;
    Se end;

    Line cur_line;

    Line take(LineType);
    void next();
    std::vector<NarrativeScene::Option> parse_options();
    std::unique_ptr<Scene> parse_narrative_scene();

  public:
    SceneParser(It begin, Se end) : cur{begin}, end{end}
    {
        next();
    }
    std::vector<std::pair<std::string, std::unique_ptr<Scene>>> parse_scenes();
};

#include "sceneparser.tpp"

#endif