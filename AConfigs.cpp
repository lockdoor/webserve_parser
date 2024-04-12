#include "Configs.hpp"

cfg::AConfigs::AConfigs(std::string const &type) : AConfig(type)
{
}

cfg::AConfigs::~AConfigs()
{
	std::vector<cfg::AConfig*>::const_iterator it = this->begin();
	while (it != this->end()) {
		delete *it;
		it++;
	}
}

std::vector<cfg::AConfig*>::const_iterator cfg::AConfigs::begin() const
{
	return _configs.begin();
}

std::vector<cfg::AConfig*>::const_iterator cfg::AConfigs::end() const
{
	return _configs.end();
}

std::size_t cfg::AConfigs::size() const
{
	return (_configs.size());
}

std::ostream & operator<<(std::ostream &o, cfg::AConfigs const &i)
{
	std::vector<cfg::AConfig*>::const_iterator it = i.begin();
	std::vector<cfg::AConfig*>::const_iterator it_in;
	cfg::Worker_processes *work;
	cfg::Http *http;
	cfg::Server *server;
	cfg::Index *index;
	cfg::Listen *listen;
	cfg::Root *root;
	cfg::Location *location;
	
	while(it != i.end()) {
		if ((work = dynamic_cast<cfg::Worker_processes*>(*it)))
			o << *work << std::endl;
		
		if ((http = dynamic_cast<cfg::Http*>(*it))) {
			o << http->getType() << " {" << std::endl;
			o << *http;
			o << "}" << std::endl;
		}

		if ((server = dynamic_cast<cfg::Server*>(*it))) {
			// o << "server size: " << server->size() << std::endl;
			o << server->getType() << " {" << std::endl;
			o << *server;
			o << "}" << std::endl;
		}

		if ((location = dynamic_cast<cfg::Location*>(*it))) {
			// o << "locationsize: " << location>size() << std::endl;
			o << location->getType() << " " << location->getLocation() << " {" << std::endl;
			o << *location;
			o << "}" << std::endl;
		}

		if ((index = dynamic_cast<cfg::Index*>(*it)))
			std::cout << *index << std::endl;

		if ((listen = dynamic_cast<cfg::Listen*>(*it)))
			std::cout << *listen;

		if ((root = dynamic_cast<cfg::Root*>(*it)))
			std::cout << *root;

		it++;
	}
	return (o);
}
