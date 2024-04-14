#include "Configs.hpp"

cfg::Http::Http(std::ifstream &file) : AGroup(file, "http")
{
	firstBracket(file);
	init(file);
	setRoot();
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

void cfg::Http::setRoot()
{
	Server *server;
	for(config_itc it = _configs.begin(); it != _configs.end(); it++) {
		if((server = dynamic_cast<cfg::Server*>(*it))) {
			if (_root.count((*server).getServerName()))
				throw (std::runtime_error ("validate http duplicate server"));
			_root[(*server).getServerName()] = (*server).getLocation();
		}
	}
}

std::string const & cfg::Http::getRoot(std::string const &server_name, std::string const &location)
{
	if(!_root.count(server_name)) 
		throw (std::runtime_error("getRoot server_name not found"));
	std::map<std::string, std::string> &locate = _root[server_name];

	if (!locate.count(location)) 
		throw (std::runtime_error("getRoot location not found"));
	
	return (locate[location]);
} 

void cfg::Http::validate() const
{}
