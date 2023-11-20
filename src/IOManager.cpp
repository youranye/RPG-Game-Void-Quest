#include "IOManager.h"

void IOManager::write(std::string const &view)
{
    os << view << std::flush;
}

std::string IOManager::read(std::string &text)
{
    getline(is, text);
}

int IOManager::readOption(int num_options)
{
    char const last_letter = 'a' + num_options - 1;

    std::string buffer{};
    while (true)
    {
        std::getline(is, buffer);

        // Validate that the chosen letter is one of the options
        if (buffer.size() == 1 && buffer[0] >= 'a' && buffer[0] <= last_letter)
        {
            break;
        }

        os << "Please enter a letter from a to " << last_letter << std::endl;
    }

    return buffer[0] - 'a';
}