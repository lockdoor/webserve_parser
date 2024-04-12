#include "Configs.hpp"
#include <iostream>

cfg::AConfig::AConfig(std::string const &type) : _type(type) {}

cfg::AConfig::AConfig(){}

cfg::AConfig::AConfig(AConfig const &ins)
{
    *this = ins;
}

cfg::AConfig & cfg::AConfig::operator=(AConfig const &rhs)
{
    if (this != &rhs)
    {
        _type = rhs._type;
    }
    return (*this);
}

cfg::AConfig::~AConfig()
{

}

// member function
std::string const & cfg::AConfig::getType() const
{
    return (_type);
}
