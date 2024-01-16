# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 01:05:23 by hlakhal-          #+#    #+#              #
#    Updated: 2024/01/16 16:49:15 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

SRC =  Location.cpp  Server.cpp webServer.cpp main.cpp parsingFile.cpp\
		setupServer.cpp Client.cpp

CXX = c++ -std=c++98 -fsanitize=address -g3

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