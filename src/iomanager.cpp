#include "iomanager.h"

void IOManager::write(std::string_view view)
{
    os << view;
}
std::string_view IOManager::read_option(std::vector<std::string> const options)
{
    char letter = 'a';
    for (auto const &str : options)
    {
        os << letter << ". " << str << '\n';
        ++letter;
    }

    std::string buffer{};

    while (true)
    {
        std::getline(is, buffer);

        if (buffer.size() == 1 && buffer[0] >= 'a' && buffer[0] < 'a' + options.size())
        {
            os << "Please enter a letter from a to " << static_cast<char>('a' + options.size() - 1) << std::endl;
            break;
        }
    }

    return options[buffer[0] - 'a'];
}