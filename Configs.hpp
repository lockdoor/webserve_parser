#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include <string>
#include <vector>
#include <map>
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
			int _level;

		public:
			AConfig(std::string const &type);
			AConfig(AConfig const &ins);
			AConfig & operator=(AConfig const &rhs);
			virtual ~AConfig();
			std::string const & getType() const;
			void end_directive(std::ifstream &file);
			bool getString(std::string &buffer, std::ifstream &file);

			void setLevel(int level);
			int getLevel() const;
			std::string indent() const;
	};

	class AConfigs : public AConfig
	{
		protected:
			std::vector<AConfig*> _configs;
			void setGroupLevel(int n, 
				std::vector<AConfig*>::const_iterator begin,
				std::vector<AConfig*>::const_iterator end
				);
		public:
			AConfigs(std::string const &type);
			virtual ~AConfigs();
			std::vector<AConfig*>::const_iterator begin() const;
			std::vector<AConfig*>::const_iterator end() const;
			std::size_t size() const;
	};

	class AGroup : public AConfigs
	{
		protected:
			void virtual init(std::ifstream &file) = 0;
			void firstBracket(std::ifstream &file);
		public:
			AGroup(std::ifstream &file, std::string const &type);
			virtual ~AGroup();	
	};

	class Configs : public AConfigs
	{
		public:
			Configs(std::string const &filename);
			~Configs();
	};

	class Http : public AGroup
	{
		private:
			void init(std::ifstream &file);
		public:
			Http(std::ifstream &file);
			~Http();
	};

	class Server : public AGroup
	{
		private:
			void init(std::ifstream &file);
		public:
			Server(std::ifstream &file);
			~Server();
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

	class Listen : public AConfig
	{
		private:
			std::pair<std::string, std::string> _listen;
		public:
			Listen(std::ifstream &file);
			~Listen();
			std::string const & first() const;
			std::string const & second() const;
	};

	class Index : public AConfig
	{
		private:
			std::vector<std::string> _indexs;
		public:
			Index(std::ifstream &file);
			~Index();
			std::vector<std::string>::const_iterator begin() const;
			std::vector<std::string>::const_iterator end() const;
	};

	class Root : public AConfig
	{
		private:
			std::string _root;
		public:
			Root(std::ifstream &file);
			~Root();
			std::string const &getRoot() const;
	};

	class Location : public AGroup
	{
		private:
			std::string _location;
			void init(std::ifstream &file);
		public:
			Location(std::ifstream &file);
			~Location();
			std::string const &getLocation() const;
	};
}

std::ostream & operator<<(std::ostream &o, cfg::AConfigs const &i);
std::ostream & operator<<(std::ostream &o, cfg::Worker_processes const &i);
std::ostream & operator<<(std::ostream &o, cfg::Index const &i);
std::ostream & operator<<(std::ostream &o, cfg::Listen const &i);
std::ostream & operator<<(std::ostream &o, cfg::Root const &i);
#endif