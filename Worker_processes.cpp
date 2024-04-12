#include "Configs.hpp"

cfg::Worker_processes::Worker_processes(std::ifstream &file) : AConfig("worker_processes")
{
    if (file.peek() <= 0) throw (std::runtime_error("Error: " + this->getType()));
    file >> _value;
    if (file.fail()) throw (std::runtime_error("Error: " + this->getType()));
    file.peek();
    char c = file.get();
    std::cout << "c: " << c << std::endl;
    if (c != ';') throw (std::runtime_error("Error: " + this->getType()));
}

cfg::Worker_processes::~Worker_processes()
{

}

int cfg::Worker_processes::getValue() const
{
    return (_value);
}

std::ostream & operator<<(std::ostream &o, cfg::Worker_processes const &i)
{
    o << i.getType() << " " << i.getValue();
    return (o);
}
