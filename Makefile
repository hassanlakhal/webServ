# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 01:05:23 by hlakhal-          #+#    #+#              #
#    Updated: 2024/01/08 18:54:02 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = web

SRC =  Location.cpp  Server.cpp webServer.cpp main.cpp

CXX = c++ -std=c++98

CXXFLAGS = -Wall -Wextra -Werror

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