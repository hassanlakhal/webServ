/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:02:58 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/25 22:46:56 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_HPP
#define M_HPP

#include "../Box.hpp"
#include <iostream>
#include <dirent.h>
#include <vector>
#include <sys/wait.h>
#include <string>
#include <filesystem>
#include <sys/stat.h>

typedef std::map<std::string, std::string> infoMap;
# define BUFFER_SIZE 1024

class Box;
void get(Box &box, int ind, int fd);
void post(Box &box, int ind, int fd);
int cgi(Client& client, Location& myLocation, std::string reqPath, std::string file, int serverID, std::string method, std::string postFile);
void deleteM(Box &box, int ind, int fd);

#endif
