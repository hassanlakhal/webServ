/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:02:58 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/19 09:15:57 by hlakhal-         ###   ########.fr       */
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
int cgi(Box& box, Location& myLocation, int fd, std::string, std::string file, int serverID, std::string method, std::string postFile);
void deleteM(Box &box, int ind, int fd);
void timeOutCgi(Box& box, int fd);
#endif
