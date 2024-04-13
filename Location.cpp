#include "Configs.hpp"

cfg::Location::Location(std::ifstream &file) : AGroup(file, "location")
{
	// parser location
	if (file.peek() <= 0) 
		throw (std::runtime_error("Error: " + this->getType()));
	if (file.eof()) 
		throw (std::runtime_error("Error: " + this->getType()));
	bool found_semicolon = getString(_location, file);
	if (found_semicolon)
		throw (std::runtime_error("Error: " + this->getType()));

	firstBracket(file);
	init(file);
}

cfg::Location::~Location(){}

void cfg::Location::init(std::ifstream &file)
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
			else if (directive == "root")
				dir = new Root(file);
			else if (directive == "redirect")
				dir = new Redirect(file);
			else
				throw(std::runtime_error(this->getType() + "Error: unknow directive " + directive));

			_configs.push_back(dir);
		} catch (std::exception const &e) {
			throw ;
		}
	}
}

std::string const & cfg::Location::getLocation() const
{
	return (_location);
}

void cfg::Location::validate() const
{
	
}