#include "Configs.hpp"

cfg::Configs::Configs(std::string const &filename) : AConfigs("configs")
{
	_http = NULL;
	std::ifstream file(filename.c_str());
	if (!file.is_open()) 
		throw (std::runtime_error("Error con not open " + filename));

    AConfig *dir;

	while(!file.eof()) {
		try {
			file.peek();
			std::string directive;
			file >> directive;
			if (file.eof() && file.fail()) break;
			if (directive == "http")
				dir = new Http(file);
			else
				throw(std::runtime_error("Error: unknow directive " + directive));

			_configs.push_back(dir);
		} catch (std::exception const &e) {
			file.close();
			throw ;
		}
	}
	// std::cout << "size: " << _configs.size() << std::endl;
	file.close();
	setHttp();
}

cfg::Configs::~Configs()
{

}

void cfg::Configs::setHttp()
{
	std::size_t n = 0;
	for(config_itc it = _configs.begin(); it != _configs.end(); it++) {
		if((_http = dynamic_cast<cfg::Http*>(*it))) {
			n++;
		}
	}
	if (!_http || n < 1)
		throw (std::runtime_error("validate Config no http or more http"));
}

std::string * cfg::Configs::getRoot(std::string const &server_name, std::string const &location) 
{
	return ((*_http).getRoot(server_name, location));
}

void cfg::Configs::validate() const
{}
