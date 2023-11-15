#ifndef IOMANAGER_HPP
#define IOMANAGER_HPP

#include <iostream>
#include <vector>

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

    /// @brief Print a list of options and have the user select one
    /// @param options Vector of options for the user to select from, taking from input stream
    /// @return a reference to the selected option 
    std::string const& read_option(std::vector<std::string> const& options);
};

#endif