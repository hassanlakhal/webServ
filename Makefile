# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 01:05:23 by hlakhal-          #+#    #+#              #
#    Updated: 2024/01/06 02:10:14 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = web

# SCR =  Location.cpp  Server.cpp webServer.cpp

# CXX = c++ -std=c++98

# CXXFLAGS = -Wall -Wextra -Werror

# all:$(NAME)

# OBJ = $(SCR:.cpp=.o)

# $(NAME):$(OBJ)
# 	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

# clean:
# 	rm -rf $(OBJ)
	
# fclean:
# 	rm -rf $(OBJ) $(NAME)

# re : fclean all

NAME = web

SRC =  Location.cpp  Server.cpp webServer.cpp main.cpp
CXXFLAGS = -Wall -Wextra -Werror

CXX = c++ -std=c++98 

all:$(NAME)

OBJ = $(SRC:.cpp=.o)


$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ) 
	
fclean:clean
	rm -rf $(NAME) 

rmfiles:
	rm -rf $(OBJ)
	
re: fclean all