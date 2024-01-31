/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:02:58 by eej-jama          #+#    #+#             */
/*   Updated: 2024/01/31 20:15:45 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_HPP
#define M_HPP

#include "../Box.hpp"
#include <iostream>
#include <dirent.h>
#include <vector>
#include <sys/wait.h>
# define BUFFER_SIZE 1024

class Box;
void get(Box &box, int ind, int fd);
void post(Box &box, int ind, int fd);
void cgi(Location& myLocation, std::string, std::string file, int serverID);
void deleteM(Box &box, int ind, int fd);

#endif
