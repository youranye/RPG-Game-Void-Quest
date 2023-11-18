#include "narrativescene.h"

#include <stdexcept>

std::vector<std::string> NarrativeScene::getOptions() const
{
    std::vector<std::string> result;
    for (auto const &option : options)
    {
        result.push_back(option.text);
    }
    return result;
}

std::string NarrativeScene::getKey(int index) const
{
    // Search each option for a match
    return options.at(index).nextKey;
}