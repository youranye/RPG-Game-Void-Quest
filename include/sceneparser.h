#pragma once
#ifndef SCENEPARSER_HPP
#define SCENEPARSER_HPP

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "scene.h"
#include "narrativescene.h"

/// @brief Exception thrown when parser encounters an error
class SceneParseException : public std::exception
{
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
        std::string text;
    };

    It cur;
    Se end;

    Line curLine;

    /// @brief Check that the current line is the correct type, advancing if true
    /// @param type Expected type of the line
    /// @return The current line, before advancing
    /// @throws `SceneParseException`
    Line take(LineType type);

    /// @brief Advance to the next line
    void next();

    /// @brief Parse a list of options
    /// @return A vector of options
    std::vector<NarrativeScene::Option> parseOptions();

    /// @brief Parse a `NarrativeScene`
    /// @return A unique_ptr to the NarrativeScene
    std::unique_ptr<Scene> parseNarrativeScene();

  public:

    /// @brief Construct a SceneParser over
    /// @param begin Iterator to the start of the text to parse
    /// @param end Iterator to the end of the text to parse
    SceneParser(It begin, Se end) : cur{begin}, end{end}
    {
        next();
    }

    /// @brief Parse the scenes
    /// @return A vector of name-Scene pairs
    std::vector<std::pair<std::string, std::unique_ptr<Scene>>> parseScenes();
};

#include "sceneparser.tpp"

#endif