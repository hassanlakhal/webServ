/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:53 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/05 14:47:32 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"

void deleteM(Box &box, int ind, int fd){
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	int serverID = box.getClients()[fd].getServerId();
	std::string reqPath = box.getClients()[fd].getPath();
	reqPath = box.removeSlach(reqPath);
	reqPath = box.FullQueryString(reqPath);
	reqPath =  myLocation.getRoot() + "/" + reqPath;
	std::string file = reqPath.substr(1);
	if(file.find_last_of('/') != std::string::npos && file.find('.') != std::string::npos)
		file = file.substr(file.find_last_of('/') + 1);
	else
		file = "";

	DIR *dir;
	// struct dirent *dent;

	if(!file.empty())
	{
		std::fstream file(reqPath.c_str());
		if(file.is_open()){
			file.close();
			std::remove(reqPath.c_str());
		}
		else
			throw errorMessage(404, serverID);
	}
	else{
			std::cout << "iiiiiiiiiiiiiiiii" << std::endl;
		if(reqPath != myLocation.getRoot() && (dir = opendir(reqPath.c_str())) != NULL){
			closedir(dir);
			std::remove(reqPath.c_str());
		}
		else
			throw errorMessage(404, serverID);
	}
}
