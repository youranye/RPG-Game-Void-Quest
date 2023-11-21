#pragma once
#ifndef SCENEPARSER_HPP
#define SCENEPARSER_HPP

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "BattleScene.h"
#include "NarrativeScene.h"
#include "Scene.h"

/// @brief Exception thrown when parser encounters an error
class SceneParseException : public std::exception
{
  public:
    char const *what() const noexcept override
    {
        return "Failed to parse";
    }
};

/// @brief Parser for scenes
/// @tparam It Iterator over char
/// @tparam Se Sentinel for It
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
        std::string attribute;
        std::string text;
    };

    It cur;
    Se end;

    std::string prefix;
    Line curLine;

    /// @brief Resolve relative keys
    /// @param key Key to resolve
    std::string resolveKey(std::string const &key);

    /// @brief Skip whitespace characters until a non-whitespace or end of input is reached
    void skipWhitespace();

    /// @brief Check that the current line is the correct type, advancing if true
    /// @param type Expected type of the line
    /// @return The current line, before advancing
    /// @throws `SceneParseException`
    Line take(LineType type);

    /// @brief Advance to the next line
    void next();

    /// @brief Parse a list of options
    /// @return A vector of options
    std::vector<NarrativeScene::Option> parseNarrativeOptions();

    /// @brief Parse a `NarrativeScene`
    /// @return A unique_ptr to the NarrativeScene
    std::unique_ptr<NarrativeScene> parseNarrativeScene();

    /// @brief Parse a `BattleScene`
    /// @return A unique_ptr to the BattleScene
    std::unique_ptr<BattleScene> parseBattleScene();

  public:
    /// @brief Construct a SceneParser over
    /// @param begin Iterator to the start of the text to parse
    /// @param end Iterator to the end of the text to parse
    SceneParser(It begin, Se end, std::string prefix) : cur{begin}, end{end}, prefix{prefix}
    {
        next();
    }

    /// @brief Parse the scenes
    /// @return A vector of name-Scene pairs
    std::vector<std::pair<std::string, std::unique_ptr<Scene>>> parseScenes();
};

#include "SceneParser.tpp"

#endif