# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 01:05:23 by hlakhal-          #+#    #+#              #
#    Updated: 2024/02/21 01:24:17 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver

SRC =  Location.cpp  Server.cpp webServer.cpp main.cpp parsingFile.cpp\
		Client.cpp Box.cpp errorMessage.cpp Response.cpp methods/Get.cpp\
		methods/Post.cpp methods/Cgi.cpp methods/Delete.cpp

CXX = c++ -std=c++98

CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

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
