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

void cfg::AConfig::end_directive(std::ifstream &file)
{
    file.peek();
    char c;
    file >> c;
	if (c != ';') {
        // std::cout << (int)c << ":" << c << std::endl;
        throw (std::runtime_error("Error: ; " + this->getType()));
    } 
}

// return true when found ; and set 
bool cfg::AConfig::getString(std::string &buffer, std::ifstream &file)
{
    file >> buffer;
    std::size_t semi_colon = buffer.find(';');
    if (semi_colon != std::string::npos) {
        std::size_t pos_end = file.tellg();
        file.seekg(pos_end - (buffer.length() - semi_colon - 1));
        buffer = buffer.substr(0, semi_colon);
        return (true);
    }
    return (false);
}
