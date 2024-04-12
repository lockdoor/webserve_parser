#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

namespace cfg
{
	class AConfig
	{
		private:
			std::string _type;
			AConfig();
		public:
			AConfig(std::string const &type);
			AConfig(AConfig const &ins);
			AConfig & operator=(AConfig const &rhs);
			virtual ~AConfig();
			std::string const & getType() const;			
	};

	class AConfigs : public AConfig
	{
		protected:
			std::vector<AConfig*> _configs;
		public:
			AConfigs(std::string const &type);
			virtual ~AConfigs();
			std::vector<AConfig*>::const_iterator begin() const;
			std::vector<AConfig*>::const_iterator end() const;
	};

	class Configs : public AConfigs
	{
		public:
			Configs(std::string const &filename);
			~Configs();
	};

	class Worker_processes : public AConfig
	{
		private:
			int _value;
		public:
			Worker_processes(std::ifstream &file);
			~Worker_processes();
			int getValue() const;
	};

	// class Http : public AConfig
	// {
	// 	private:
	// 		std::vector<AConfig*> _configs;
	// 	public:
	// 		Http(std::ifstream &file);
	// 		~Http();
	// };

	// class Index : public AConfig
	// {
	// 	private:
	// 		std::vector<std::string> _indexs;
	// 	public:
	// 		Index(std::ifstream &file);
	// 		~Index();
	// };
}

std::ostream & operator<<(std::ostream &o, cfg::AConfigs const &i);
std::ostream & operator<<(std::ostream &o, cfg::Worker_processes const &i);
// std::ostream & operator<<(std::ostream &o, cfg::Http const &i);

#endif