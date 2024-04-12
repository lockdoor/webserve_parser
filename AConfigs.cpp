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

std::ostream & operator<<(std::ostream &o, cfg::AConfigs const &i)
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
