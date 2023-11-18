#include "narrativescene.h"

#include <stdexcept>

std::vector<std::string> NarrativeScene::get_options() const
{
    std::vector<std::string> result;
    for (auto const &option : options)
    {
        result.push_back(option.text);
    }
    return result;
}

std::string NarrativeScene::getKey(std::string const& optionText) const
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