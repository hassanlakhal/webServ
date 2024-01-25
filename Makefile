# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 01:05:23 by hlakhal-          #+#    #+#              #
#    Updated: 2024/01/25 21:12:49 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

SRC =  Location.cpp  Server.cpp webServer.cpp main.cpp parsingFile.cpp\
		Client.cpp Box.cpp errorMessage.cpp Repence.cpp

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