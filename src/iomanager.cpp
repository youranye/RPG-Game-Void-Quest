#include "iomanager.h"

void IOManager::write(std::string const &view)
{
    os << view;
}
std::string const &IOManager::read_option(std::vector<std::string> const &options)
{
    // Print the list of options
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

        // Validate that the chosen letter is one of the options
        if (buffer.size() == 1 && buffer[0] >= 'a' && buffer[0] < 'a' + options.size())
        {
            break;
        }

        os << "Please enter a letter from a to "
           << static_cast<char>('a' + options.size() - 1) // Final letter of options
           << std::endl;
    }

    return options[buffer[0] - 'a'];
}