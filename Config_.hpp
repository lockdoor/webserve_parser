#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <map>
#include <string>

#define MAIN_TYPE 0
#define HTTP_TYPE 1
#define SERVER_TYPE 2
#define LISTEN_TYPE 3

typedef struct conf
{
	int type;
} t_conf;

typedef struct server
{
	int type;
	std::map<std::string, std::vector<std::string> > listen;
} t_server;

typedef struct http
{
	int type;
	std::vector<t_server *> server;
} t_http;

class Config
{
private:
	t_http _http;
public:
	Config(std::string const &filename);
	~Config();

	void parser_http(std::ifstream &file);
	void http(std::ifstream &file, t_conf *conf);
	void server(std::ifstream &file, t_conf *conf);
	void block(std::ifstream &file, t_conf *conf);
	void listen(std::ifstream &file, t_conf *conf);

	void show()const;
};

#endif
