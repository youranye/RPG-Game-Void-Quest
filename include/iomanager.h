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

    void write(std::string_view);
    std::string_view read_option(std::vector<std::string> const);
};

#endif