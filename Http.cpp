#include "Configs.hpp"

cfg::Http::Http(std::ifstream &file) : AConfigs("http")
{
	std::string directive;
	file.peek();

	if (file.eof()) 
		throw (std::runtime_error("Error: " + this->getType()));
	
	file >> directive;
	
	if (directive != "{") 
		throw (std::runtime_error("Error: " + this->getType() + " '{' not found"));

	while(true) {
		try {
			file.peek();
			if (file.eof()) 
				throw (std::runtime_error("Error: " + this->getType() + " '}' not found"));
			AConfig *dir;
			file >> directive;
			if (directive == "}") break;
			else if (directive == "index")
				dir = new Index(file);
			else if (directive == "server")
				dir = new Server(file);
			else
				throw(std::runtime_error(this->getType() + "Error: unknow directive " + directive));
			_configs.push_back(dir);
		} catch (std::exception const &e) {
			throw ;
		}
	}
}

cfg::Http::~Http()
{

}
