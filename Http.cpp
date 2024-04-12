#include "Configs.hpp"

cfg::Http::Http(std::ifstream &file) : AConfig("http")
{
    std::string directive;
    if (!file.peek()) throw (std::runtime_error("Error: http"));
    file >> directive;
    if (directive != "{") throw (std::runtime_error("Error: http '{' not found"));

	while(true) {
        if (file.peek() < 0) throw (std::runtime_error("Error: http '}' not found"));
		try {
			AConfig *dir;
			file >> directive;
            if (directive == "}") break;
			// else if (directive == "index")
			// 	AConfig *dir = new Http(file);
			else
			{
				file.close();
				throw(std::runtime_error("Error: unknow directive " + directive));
			}
			_configs.push_back(dir);
		} catch (std::exception const &e) {
			throw ;
		}
	}
}

cfg::Http::~Http()
{

}

std::ostream & operator<<(std::ostream &o, cfg::Http const &i)
{
	std::vector<cfg::AConfig*>::const_iterator it = i.begin();
	cfg::Worker_processes *work;
	while(it != i.end()) {
		
		if ((work = dynamic_cast<cfg::Worker_processes*>(*it)))
			o << *work << std::endl;
		it++;
	}
	return (o);
}