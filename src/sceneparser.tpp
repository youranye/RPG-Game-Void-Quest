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
    // Skip leading whitespace
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

    // Check what the first character is to determine the type of line
    switch (*cur)
    {
    case '#':
        ++cur;
        if (cur != end && *cur == '#')
        {
            // ## Header 2
            ++cur;
            type = LineType::H2;
        }
        else
        {
            // # Header 1
            type = LineType::H1;
        }
        break;

    case '-':
        // - Option
        ++cur;
        type = LineType::Option;
        break;

    default:
        // Some other text
        type = LineType::Text;
        break;
    }

    // Skip trailing whitespace
    while (cur != end && std::isspace(*cur))
    {
        ++cur;
    }

    std::string text{};

    // Read into text until the end of the line or end of the input
    while (cur != end && *cur != '\n')
    {
        text.push_back(*cur);
        ++cur;
    }

    // Skip the newline if we're not at the end
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
        // Throw if there isn't an ->
        if (idx == std::string::npos)
        {
            throw SceneParseException{};
        }

        // Split at ->
        auto const name = cur_line.text.substr(0, idx);
        auto const optionText = cur_line.text.substr(idx + 4);
        options.push_back(NarrativeScene::Option{name, optionText});
        next();
    }
    return options;
}

template <class It, class Se> std::unique_ptr<Scene> SceneParser<It, Se>::parse_narrative_scene()
{
    std::string text{};
    // Read the flavor text
    while (cur_line.type == LineType::Text)
    {
        text.append(cur_line.text);
        next();
    }
    // Read the options
    auto const options = parse_options();
    return std::make_unique<NarrativeScene>(text, options);
}

template <class It, class Se>
std::vector<std::pair<std::string, std::unique_ptr<Scene>>> SceneParser<It, Se>::parse_scenes()
{
    std::vector<std::pair<std::string, std::unique_ptr<Scene>>> parsed_scenes{};

    // Read all the narrative scenes
    // TODO: Implement BattleScene parsing
    while (cur_line.type != LineType::None)
    {
        auto name = take(LineType::H1).text;
        auto scene = parse_narrative_scene();
        parsed_scenes.push_back({name, std::move(scene)});
    }

    return parsed_scenes;
}

#endif