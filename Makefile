# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 12:08:43 by droied            #+#    #+#              #
#    Updated: 2025/02/18 23:10:23 by ncastell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               FT_IRC                                         #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

NAME        = ircserv
CC 			= c++
CFLAGS 		= -Wall -Wextra -Werror -std=c++98 -I $(INCLUDE_PATH)

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               SOURCES                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

SOURCES_PATH    = ./src
INCLUDE_PATH	= ./inc
OBJECTS_PATH    = ./obj

HEADER = $(INCLUDE_PATH)/IRC.hpp $(INCLUDE_PATH)/Exception.hpp 
SOURCES = main.cpp Exception.cpp IRC.cpp

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               OBJECTS                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

OBJECTS = $(addprefix $(OBJECTS_PATH)/, ${SOURCES:.cpp=.o})
DEPS = $(addprefix $(OBJECTS_PATH)/, ${SOURCES:.cpp=.d})

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               COLORS                                         #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

RED=\033[0;31m
CYAN=\033[0;36m
GREEN=\033[0;32m
YELLOW=\033[0;33m
WHITE=\033[0;97m
BLUE=\033[0;34m
NC=\033[0m # No color

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               MANDATORY RULES                                #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJECTS)
	@printf "$(CYAN)$@ Compiled$(NC)\n"
	@$(CC) $(CFLAGS) $^ -o $(NAME)

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.cpp Makefile $(HEADER)
	@printf "$(CYAN)Compiling $@$(NC)\n";
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(CYAN)Cleaning objects and libraries$(NC)\n";
	@rm -rf $(OBJECTS_PATH) 

fclean : clean
	@printf "$(CYAN)Cleaning objects, libraries and executable$(NC)\n";
	@rm -rf $(NAME)

re: fclean all

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               MY RULES                                          #
# ╚══════════════════════════════════════════════════════════════════════════╝ #   
	
.PHONY: all clean fclean re
