#include "Configs.hpp"

cfg::Http::Http(std::ifstream &file) : AGroup(file, "http")
{
	firstBracket(file);
	init(file);
}

cfg::Http::~Http()
{

}

void cfg::Http::init(std::ifstream &file)
{
	while(true) {
		try {
			std::string directive;
			file.peek();
			if (file.eof()) 
				throw (std::runtime_error("Error: " + this->getType() + " '}' not found"));
			AConfig *dir;
			file >> directive;
			if (directive == "}") break;
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

void cfg::Http::validate() const
{}
