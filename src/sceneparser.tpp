#pragma once
#ifndef SCENEPARSER_TPP
#define SCENEPARSER_TPP

#include "narrativescene.h"
#include "sceneparser.h"

#include <algorithm>

template <class It, class Se> void SceneParser<It, Se>::skipWhitespace()
{
    while (cur != end && std::isspace(*cur))
    {
        ++cur;
    }
}

template <class It, class Se> typename SceneParser<It, Se>::Line SceneParser<It, Se>::take(LineType type)
{
    if (curLine.type == type)
    {
        auto ret = curLine;
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
    skipWhitespace();

    if (cur == end)
    {
        curLine = {LineType::None, {}};
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
    skipWhitespace();

    std::string attribute{};
    if (cur != end && *cur == '[')
    {
        ++cur;
        while (cur != end && *cur != ']')
        {
            attribute.push_back(*cur);
            ++cur;
        }
        if (cur == end)
        {
            throw SceneParseException{};
        }
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

    curLine = {type, attribute, text};
}

template <class It, class Se> std::vector<NarrativeScene::Option> SceneParser<It, Se>::parseOptions()
{
    take(LineType::H2);
    std::vector<NarrativeScene::Option> options{};
    while (curLine.type == LineType::Option)
    {
        auto const idx = curLine.text.find(" -> ");
        // Throw if there isn't an ->
        if (idx == std::string::npos)
        {
            throw SceneParseException{};
        }

        // Split at ->
        auto const name = curLine.text.substr(0, idx);
        auto const optionText = curLine.text.substr(idx + 4);
        options.push_back(NarrativeScene::Option{name, optionText});
        next();
    }
    return options;
}

template <class It, class Se> std::unique_ptr<NarrativeScene> SceneParser<It, Se>::parseNarrativeScene()
{
    std::string text{};
    // Read the flavor text
    while (curLine.type == LineType::Text)
    {
        text.append(curLine.text);
        next();
    }
    // Read the options
    auto const options = parseOptions();
    return std::make_unique<NarrativeScene>(text, options);
}


template <class It, class Se> std::unique_ptr<BattleScene> SceneParser<It, Se>::parseBattleScene()
{
    // Read the options
    take(LineType::H2);
    auto const enemyName = take(LineType::Option).text;
    return std::make_unique<BattleScene>(enemyName);
}

template <class It, class Se>
std::vector<std::pair<std::string, std::unique_ptr<Scene>>> SceneParser<It, Se>::parseScenes()
{
    std::vector<std::pair<std::string, std::unique_ptr<Scene>>> parsedScenes{};

    while (curLine.type != LineType::None)
    {
        auto line = take(LineType::H1);

        std::unique_ptr<Scene> scene;
        if (line.attribute == "battle")
        {
            scene = parseBattleScene();
        }
        else
        {
            scene = parseNarrativeScene();
        }

        parsedScenes.push_back({line.text, std::move(scene)});
    }

    return parsedScenes;
}

#endif