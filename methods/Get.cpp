/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:59:17 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/09 17:22:54 by eej-jama         ###   ########.fr       */
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
	std::cout << "lpath jdidi-- : " << reqPathLoc << "\n";
	std::string codeHTML = "<!DOCTYPE html><html lang=\"en\"><head><link rel=\"icon\" href=\"/favicon.ico\" type=\"image/x-icon\"><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title></head><body><ul>";
	codeHTML += "<h2>Listed files</h2>";
	if((dir = opendir(reqPath.c_str())) != NULL){
		while ((dent = readdir(dir)) != NULL)
		{
			if(strcmp(dent->d_name, ".") && strcmp(dent->d_name, ".."))
			{
				std::cout << "listed file : " << dent->d_name << "\n";
				// size_t len = myLocation.getRoot().length();
				codeHTML += "<li><a href=\"" + reqPathLoc + tmp + dent->d_name + "\">" + dent->d_name + "</a></li>";
			}
		}
	}
	else
		throw errorMessage(404, serverID);
	codeHTML += "</ul></body></html>";
	closedir(dir);
	// std::cout << "code : " << codeHTML << std::endl;
	throw errorMessage(200,codeHTML);
}


void get(Box &box, int ind, int fd){
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	int serverID = box.getClients()[fd].getServerId();
	std::string reqPath = box.getClients()[fd].getPath();
	reqPath = box.removeSlach(reqPath);
	reqPath = box.FullQueryString(reqPath);
	// std::cout << "path : " << reqPath << std::endl;
	std::string file = reqPath;
	std::cout << "file : " << file << std::endl;
	if(file.find_last_of('/') != std::string::npos && file.find('.') != std::string::npos)
		file = file.substr(file.find_last_of('/') + 1);
	else
		file = "";
	// exit(0);
	if(!file.empty()){
	// std::cout << " file arrived : " << reqPath << std::endl;

		// reqPath = reqPath.substr(1);
		reqPath = reqPath.substr(0, reqPath.find_last_of('/'));
		// std::cout << "my path : " << reqPath << std::endl;
		cgi(box, myLocation, fd, reqPath.substr(1), file, serverID, "GET", "");
	}
	else
	{

		if(myLocation.getAutoIndex() == "on")
		{

			std::set<std::string>::iterator it;
			if(myLocation.getIndexes().size() > 2){
				it = myLocation.getIndexes().begin();
				for (size_t i = 2; i < myLocation.getIndexes().size(); i++, it++)
				{
					file =  *it;
					if(!cgi(box, myLocation, fd, reqPath.substr(1), file, serverID, "GET", ""))
						continue;
				}
			}else{
				it = myLocation.getIndexes().begin();
				for (size_t i = 0; i < 2; i++, it++)
				{
					file = *it;

					if(!cgi(box, myLocation, fd, reqPath.substr(1), file, serverID, "GET", "")){
						continue;
					}

				}
			}
		}
		if(myLocation.getListingDir() == "on"){
			listing_dir(fd, myLocation, box);
		}
		else{

			throw errorMessage(403, box.getClients()[fd].getServerId());
		}
	}


	// std::cout << "GET method - :" << std::endl;
	// std::cout << box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation().at(ind).getPath() << std::endl;
	// std::cout << reqPath << "--------" << file << std::endl;

}



