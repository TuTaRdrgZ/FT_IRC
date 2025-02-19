CLIENT= client
SERVER= ircserv
TEST= test

SERVER_SRC= server.cpp
SERVER_OBJ= $(SERVER_SRC:.cpp=.o)

CLIENT_SRC= client.cpp
CLIENT_OBJ= $(CLIENT_SRC:.cpp=.o)

TEST_SRC= test_ft_irc.cpp
TEST_OBJ= $(TEST_SRC:.cpp=.o)

CC=c++
CFLAGS= -std=c++98 -Wall -Wextra -Werror -g

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(SERVER)

client: $(CLIENT_OBJ)
	$(CC) -o $(CLIENT) $(CLIENT_OBJ) $(CFLAGS)

ircserv: $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) $(CFLAGS)

test: $(SERVER) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(CFLAGS) -o $(TEST)
	./test

re: fclean all

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(TEST)

.PHONY: all clean fclean re server client test
