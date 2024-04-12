#include "Configs.hpp"

cfg::Root::Root(std::ifstream &file) : AConfig("root")
{
    if (file.peek() <= 0) 
        throw (std::runtime_error("Error: " + this->getType()));
    if (file.eof()) 
        throw (std::runtime_error("Error: " + this->getType()));
    bool found_semicolon = getString(_root, file);
    if (!found_semicolon) end_directive(file);
}

cfg::Root::~Root() {}

std::string const & cfg::Root::getRoot() const
{
    return (_root);
}

std::ostream & operator<<(std::ostream &o, cfg::Root const &i)
{
    o << i.getType() << " " << i.getRoot() << ";" << std::endl;
    return (o);
}