#include "Config.hpp"
#include <fstream>
#include <iostream>

Config::Config(std::string const &filename)
{
	std::ifstream file(filename);

	parser_http (file);
	file.close();
}

Config::~Config()
{
}

void Config::parser_http(std::ifstream &file)
{
	if (!file.peek()) {
		std::cerr << "Error in parser_http" << std::endl;
		exit (1);
	}
	std::string directive;
	file >> directive;
	if (directive == "http") {
		std::cout << "http block" << std::endl;
		_http.type = HTTP_TYPE;
		block(file, reinterpret_cast<t_conf*>(&_http));
	}
	else {
		std::cerr << "Error: parser_http" << std::endl;
	}
}

void Config::http(std::ifstream &file, t_conf *conf)
{
	if (!file.peek()) {
		std::cerr << "Error in http: " << conf->type << std::endl;
		exit (1);
	}
	std::string directive;
	file >> directive;
	// std::cout << directive << std::endl;

	t_http *h = reinterpret_cast<t_http*>(&conf);

	// if (directive == "}") {
	// 	return ;
	// }
	if (directive == "server") {
		t_server *s = new t_server;
		s->type = SERVER_TYPE;
		h->server.push_back(s);
		block(file, reinterpret_cast<t_conf*>(s));
	} 
	else
	{
		std::cerr << "unknow directive" << std::endl;
		exit (1);
	}
}

void Config::block(std::ifstream &file, t_conf *conf)
{
	std::string block;
	if (!file.peek()) {
		std::cerr << "Error in block: " << conf->type << std::endl;
		exit (1);
	}
	file >> block;
	if (block != "{") {
		std::cerr << "Error in block: " << conf->type 
		<< ", can not find {" << std::endl;
		exit (1);
	}

	if (conf->type == HTTP_TYPE) {
		http(file, conf);
	}
	else if (conf->type == SERVER_TYPE) {
		server(file, conf);
	}
}



void Config::server(std::ifstream &file, t_conf *conf)
{
	// t_server *s = reinterpret_cast<t_server*>(conf);

	if (!file.peek()) {
		std::cerr << "Error on server block" << std::endl;
		exit(1);
	}

	std::string directive;
	file >> directive;
	std::cout << "debug from server " << directive << std::endl; 
	if (directive == "}") {
		return ;
	}
	else if (directive == "listen")
	{
		listen(file, conf);
	}
	else 
	{
		std::cerr << "unknow directive" << std::endl;
		exit(1);		
	}

	std::cout << "server block" << std::endl;

	// block(file, reinterpret_cast<t_conf*>(server));
	// parser (file, reinterpret_cast<t_conf*>(server));
}

void Config::listen(std::ifstream &file, t_conf *conf)
{
	// t_server *s = reinterpret_cast<t_server*>(conf);
	(void) conf;

	if (!file.peek()) {
		std::cerr << "Error on listen" << std::endl;
		exit(1);
	}

	std::string value;
	file >> value;
	
	std::cout << "listen directive: " << value << std::endl;
	server(file, conf);
}