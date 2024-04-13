#include "Configs.hpp"

cfg::Server::Server(std::ifstream &file) : AGroup(file, "server")
{
	firstBracket(file);
	init(file);
}

cfg::Server::~Server() {}

void cfg::Server::init(std::ifstream &file)
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
			else if (directive == "index")
				dir = new Index(file);
			else if (directive == "listen")
				dir = new Listen(file);
			else if (directive == "root")
				dir = new Root(file);
			else if (directive == "location")
				dir = new Location(file);
			else
				throw(std::runtime_error(this->getType() + "Error: unknow directive " + directive));

			_configs.push_back(dir);
		} catch (std::exception const &e) {
			throw ;
		}
	}
}