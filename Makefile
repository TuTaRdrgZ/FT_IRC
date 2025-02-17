CLIENT= client
SERVER= server

SERVER_SRC= server.cpp
CLIENT_SRC= client.cpp

SERVER_OBJ= $(SERVER_SRC:.cpp=.o)
CLIENT_OBJ= $(CLIENT_SRC:.cpp=.o)

CC=c++
CFLAGS= -std=c++98 -Wall -Wextra -Werror -g

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(CLIENT) $(SERVER)

client: $(CLIENT_OBJ)
	$(CC) -o $(CLIENT) $(CLIENT_OBJ) $(CFLAGS)

server: $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) $(CFLAGS)

re: fclean all

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

.PHONY: all clean fclean re server client
