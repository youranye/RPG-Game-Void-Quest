#ifndef IOMANAGER_HPP
#define IOMANAGER_HPP

#include <iostream>
#include <vector>
#include <string>

class IOManager
{
  private:
    std::istream &is;
    std::ostream &os;

  public:
    IOManager(std::istream &is, std::ostream &os) : is{is}, os{os}
    {
    }
    virtual ~IOManager() = default;

    /// @brief Write a string to the output stream
    /// @param text Text to write
    void write(std::string const& text);

    /// Read a string into the input stream
    void read(std::string &text);

    /// @brief Have the user select a letter starting from a, up to the number of options available
    /// @param numOptions Number of options for the user to select from, taking from input stream
    /// @return The index of the selected option, starting from 0
    int readOption(int numOptions);
};

#endif