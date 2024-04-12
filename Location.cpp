#include "Configs.hpp"

cfg::Location::Location(std::ifstream &file) : AConfigs("location")
{
	// parser location
	if (file.peek() <= 0) 
		throw (std::runtime_error("Error: " + this->getType()));
	if (file.eof()) 
		throw (std::runtime_error("Error: " + this->getType()));
	bool found_semicolon = getString(_location, file);
	if (found_semicolon)
		throw (std::runtime_error("Error: " + this->getType()));

	// parser block
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
			else if (directive == "root")
				dir = new Root(file);
			else
				throw(std::runtime_error(this->getType() + "Error: unknow directive " + directive));
			_configs.push_back(dir);
		} catch (std::exception const &e) {
			throw ;
		}
	}
}

cfg::Location::~Location(){}

std::string const & cfg::Location::getLocation() const
{
	return (_location);
}