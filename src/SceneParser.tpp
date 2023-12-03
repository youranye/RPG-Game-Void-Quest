#pragma once
#ifndef SCENEPARSER_TPP
#define SCENEPARSER_TPP

#include "NarrativeScene.h"
#include "SceneParser.h"

#include <algorithm>

/// @brief Resolve relative keys
/// @param key Key to resolve
template <class It, class Se> std::string SceneParser<It, Se>::resolveKey(std::string const &key)
{
    if (key.size() == 0)
    {
        throw SceneParseException{};
    }

    return key[0] == '#' ? prefix + key : key;
}

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
        curLine = {LineType::None, {}, {}};
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

    // Skip trailing whitespace
    skipWhitespace();

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

template <class It, class Se> std::vector<NarrativeScene::Option> SceneParser<It, Se>::parseNarrativeOptions()
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
        auto const optionText = curLine.text.substr(0, idx);
        std::string key = resolveKey(curLine.text.substr(idx + 4));

        options.push_back(NarrativeScene::Option{optionText, key});
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
    auto const options = parseNarrativeOptions();
    return std::make_unique<NarrativeScene>(text, options);
}

template <class It, class Se> std::unique_ptr<BattleScene> SceneParser<It, Se>::parseBattleScene()
{
    // Read the enemy
    take(LineType::H2);
    auto const enemyName = take(LineType::Option).text;

    // Read the key of the next scene
    take(LineType::H2);
    auto const nextKey = resolveKey(take(LineType::Option).text);

    return std::make_unique<BattleScene>(enemyName, nextKey);
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