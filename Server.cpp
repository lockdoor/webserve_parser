#include "Configs.hpp"

cfg::Server::Server(std::ifstream &file) : AGroup(file, "server")
{
	firstBracket(file);
	init(file);
	setServerName();
	setRoot();
	setLocation();
	// validate();
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
			else if (directive == "server_name")
				dir = new Server_name(file);
			else if (directive == "root")
				dir = new Root(file);
			else if (directive == "location")
				dir = new Location(file);
			else if (directive == "error_page")
				dir = new Error_page(file);
			else if (directive == "client_max_body")
				dir = new Client_max_body(file);
			else
				throw(std::runtime_error(this->getType() + "Error: unknow directive " + directive));

			_configs.push_back(dir);
		} catch (std::exception const &e) {
			throw ;
		}
	}
}

std::string const & cfg::Server::getServerName()const
{
	return (_server_name);
}

void cfg::Server::setServerName()
{
	/* server mush have 1 server_name */
	_server_name = "";
	std::size_t n = 0;
	for(config_itc it = _configs.begin(); it != _configs.end(); it++) {
		Server_name *name;
		if ((name=dynamic_cast<Server_name*>(*it))) {
			n++ ;
			_server_name = (*name).str();
		}
		if (n > 1) throw(std::runtime_error("validate server_name on server"));
	}
	if (_server_name.length() == 0)
		throw(std::runtime_error("validate server_name on server"));
}

void cfg::Server::setRoot()
{
	std::size_t n = 0;
	_root = "";
	for(config_itc it = _configs.begin(); it != _configs.end(); it++) {
		Root *root;
		if ((root = dynamic_cast<cfg::Root*>(*it))) {
			_root = (*root).str();
			n++ ;
		}
		if (n > 1) throw (std::runtime_error("validate root on location"));
	}

	if (n == 0) {
		for (config_itc it = _configs.begin(); it != _configs.end(); it++) {
			Location *location;
			if ((location = dynamic_cast<cfg::Location*>(*it))) {
				if(!count_root((*location).begin(), (*location).end()))
					throw (std::runtime_error("validate root on location"));
			}
		}
	}
}

std::string const & cfg::Server::getRoot() const
{
	return (_root);
}

void cfg::Server::setLocation()
{
	std::size_t n = 0;
	for(config_itc it = _configs.begin(); it != _configs.end(); it++) {
		Location *location;
		if((location = dynamic_cast<cfg::Location*>(*it))) {

			if(_location.count((*location).getLocation()))
				throw (std::runtime_error ("validate server duplicate location"));

			if((*location).getRoot().length())
				_location[(*location).getLocation()] = (*location).getRoot();
			else
				_location[(*location).getLocation()] = _root;
			n++ ;
		}
	}
	if(!n) throw (std::runtime_error ("validate server not have location"));
}

std::map<std::string, std::string> const & cfg::Server::getLocation() const
{
	return (_location);
}

void cfg::Server::validate() const
{
}