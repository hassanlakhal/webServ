/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:59:17 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/27 17:03:03 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"


void listing_dir(int fd, Location myLocation, Box& box){
	(void)fd;
	DIR *dir;
	std::string tmp = "/";
	struct dirent *dent;
	(void)myLocation;
	int serverID = box.getClients()[fd].getServerId();
	std::string reqPath = box.getClients()[fd].getPath();
	std::string reqPathLoc = box.getClients()[fd].getPathLoc();
	if(reqPathLoc == "/")
		tmp = "";
	std::string codeHTML = "<!DOCTYPE html><html lang=\"en\"><head><link rel=\"icon\" href=\"/favicon.ico\" type=\"image/x-icon\"><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title></head><body><ul>";
	codeHTML += "<h2>Listed files</h2>";
	if((dir = opendir(reqPath.c_str())) != NULL){
		while ((dent = readdir(dir)) != NULL)
		{
			if(strcmp(dent->d_name, ".") && strcmp(dent->d_name, ".."))
			{
				codeHTML += "<li><a href=\"" + reqPathLoc + tmp + dent->d_name + "\">" + dent->d_name + "</a></li>";
			}
		}
	}
	else
		throw errorMessage(404, serverID);
	codeHTML += "</ul></body></html>";
	closedir(dir);
	throw errorMessage(200,codeHTML);
}


void get(Box &box, int ind, int fd){
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	int serverID = box.getClients()[fd].getServerId();
	std::string reqPath = box.getClients()[fd].getPath();
	char get_path[PATH_MAX];
	char current_path[PATH_MAX];
	char root_path[PATH_MAX];
	reqPath = box.removeSlach(reqPath);
	reqPath = box.getClients()[fd].FullQueryString(reqPath);
	std::string file = reqPath;
	reqPath = reqPath.substr(1);
	if(file.find_last_of('/') != std::string::npos && file.find('.') != std::string::npos)
		file = file.substr(file.find_last_of('/') + 1);
	else
		file = "";



	realpath(reqPath.c_str(), get_path);
	std::string sd(get_path);
	realpath(".", current_path);
	std::string sc(current_path);
	realpath(myLocation.getRoot().c_str(), root_path);
	std::string sr(root_path);
	if(sd.find(sc) == std::string::npos || sd.find(sr) == std::string::npos)
		throw errorMessage(403, serverID);




	struct stat file_stat;
	struct stat fileIndstat;

	if(stat(reqPath.c_str(), &file_stat) != 0)
		throw errorMessage(404, serverID);
	else
	{
		if(!S_ISDIR(file_stat.st_mode))
			cgi( box.getClients()[fd], myLocation, reqPath, file, serverID, "GET", "");
		else
		{
			if(myLocation.getAutoIndex() == "on")
			{
				std::vector<std::string>::const_iterator it;
				if(myLocation.getIndexes().size()){
					it = myLocation.getIndexes().begin();
					for (size_t i = 0; i < myLocation.getIndexes().size(); i++, it++)
					{
						file =  *it;
						std::string path = reqPath + "/" + file;
						std::string type = "text/html";
						stat(path.c_str(),&fileIndstat);
						if(S_ISDIR(fileIndstat.st_mode))
						{
							std::string pathLocation = myLocation.getPath() + "/" + file;
							throw errorMessage(301,pathLocation,type);
						}
						if(!cgi(box.getClients()[fd], myLocation, reqPath + "/" + file, file, serverID, "GET", ""))
							continue;
					}
				}
			}
			if(myLocation.getListingDir() == "on")
				listing_dir(fd, myLocation, box);
			else
				throw errorMessage(403, box.getClients()[fd].getServerId());
		}
	}
}



