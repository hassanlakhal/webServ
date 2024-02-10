/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:59:17 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/10 23:50:21 by eej-jama         ###   ########.fr       */
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
	reqPath = reqPath.substr(1);
	if(file.find_last_of('/') != std::string::npos && file.find('.') != std::string::npos)
		file = file.substr(file.find_last_of('/') + 1);
	else
		file = "";

	struct stat file_stat;

	if(stat(reqPath.c_str(), &file_stat) != 0)
		throw errorMessage(404, serverID);
	else
	{
		if(!S_ISDIR(file_stat.st_mode)){

			// reqPath = reqPath.substr(0, reqPath.find_last_of('/'));
			cgi(box, myLocation, fd, reqPath, file, serverID, "GET", "");
		}
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
						if(!cgi(box, myLocation, fd, reqPath + "/" + file, file, serverID, "GET", ""))
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






	// exit(0);
	if(!file.empty()){
	// std::cout << " file arrived : " << reqPath << std::endl;

		// reqPath = reqPath.substr(1);
		// std::cout << "my path : " << reqPath << std::endl;
	}
	else
	{


	}


	// std::cout << "GET method - :" << std::endl;
	// std::cout << box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation().at(ind).getPath() << std::endl;
	// std::cout << reqPath << "--------" << file << std::endl;

}



