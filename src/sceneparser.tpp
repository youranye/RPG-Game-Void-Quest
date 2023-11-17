#pragma once
#ifndef SCENEPARSER_TPP
#define SCENEPARSER_TPP

#include "narrativescene.h"
#include "sceneparser.h"

#include <algorithm>

template <class It, class Se> typename SceneParser<It, Se>::Line SceneParser<It, Se>::take(LineType type)
{
    if (cur_line.type == type)
    {
        auto ret = cur_line;
        next();
        return ret;
    }
    else
    {
        throw SceneParseException{};
    }
}

template <class It, class Se> void SceneParser<It, Se>::next()
{
    while (cur != end && std::isspace(*cur))
    {
        ++cur;
    }

    if (cur == end)
    {
        cur_line = {LineType::None, {}};
        return;
    }

    LineType type;

    switch (*cur)
    {
    case '#':
        ++cur;
        if (cur != end && *cur == '#')
        {
            ++cur;
            type = LineType::H2;
        }
        else
        {
            type = LineType::H1;
        }
        break;

    case '-':
        ++cur;
        type = LineType::Option;
        break;

    default:
        type = LineType::Text;
        break;
    }
    while (cur != end && std::isspace(*cur))
    {
        ++cur;
    }

    std::string text{};

    while (cur != end && *cur != '\n')
    {
        text.push_back(*cur);
        ++cur;
    }

    if (cur != end)
    {
        ++cur;
    }

    cur_line = {type, text};
}

template <class It, class Se> std::vector<NarrativeScene::Option> SceneParser<It, Se>::parse_options()
{
    take(LineType::H2);
    std::vector<NarrativeScene::Option> options{};
    while (cur_line.type == LineType::Option)
    {
        auto const idx = cur_line.text.find(" -> ");
        if (idx == std::string::npos) {
            throw SceneParseException{};
        }
        options.push_back(NarrativeScene::Option{cur_line.text.substr(0, idx), cur_line.text.substr(idx + 4)});
        next();
    }
    return options;
}

template <class It, class Se> std::unique_ptr<Scene> SceneParser<It, Se>::parse_narrative_scene()
{
    std::string text{};
    while (cur_line.type == LineType::Text)
    {
        text.append(cur_line.text);
        next();
    }
    auto options = parse_options();
    return std::make_unique<NarrativeScene>(text, options);
}

template <class It, class Se>
std::vector<std::pair<std::string, std::unique_ptr<Scene>>> SceneParser<It, Se>::parse_scenes()
{
    std::vector<std::pair<std::string, std::unique_ptr<Scene>>> parsed_scenes{};

    while (cur_line.type != LineType::None)
    {
        auto name = take(LineType::H1).text;
        auto scene = parse_narrative_scene();
        parsed_scenes.push_back({name, std::move(scene)});
    }

    return parsed_scenes;
}

#endif