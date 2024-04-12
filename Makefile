NAME = webserve

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = main.cpp AConfig.cpp AConfigs.cpp Configs.cpp Worker_processes.cpp

HEADERS = Configs.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
	./$(NAME)

$(OBJS): %.o: %.cpp $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all