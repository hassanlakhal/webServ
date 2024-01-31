/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:59:17 by eej-jama          #+#    #+#             */
/*   Updated: 2024/01/31 10:48:32 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"


void listing_dir(int fd, Location myLocation){
	(void)fd;
	DIR *dir;
	struct dirent *dent;
	std::string codeHTML = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title></head><body><li>";
	if((dir = opendir(myLocation.getPath().substr(1).c_str())) != NULL){
		while ((dent = readdir(dir)) != NULL)
		{
			if(strcmp(dent->d_name, ".") && strcmp(dent->d_name, ".."))
				codeHTML += "<ul><a href=\"" + myLocation.getPath() + "/" + dent->d_name + "\">" + dent->d_name + "</a></ul>";
		}

	}

	codeHTML += "</li></body></html>";
	// while ()
	// {
	// 	/* code */
	// }

	// write(fd, codeHTML.c_str(), codeHTML.length());
}

void get(Box &box, int ind, int fd){
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	std::string reqPath = box.getClients()[fd].getPath();
	std::string file = reqPath.substr(1);
	if(file.find_last_of('/') != std::string::npos)
		file = file.substr(file.find_last_of('/') + 1);
	else
		file = "";

	if(!file.empty()){
		//check if the file is not exist
		cgi(file);
	}
	else{
		if(myLocation.getAutoIndex() == "on")
		{
			std::set<std::string>::iterator it;
			if(myLocation.getIndexes().size() > 2){
				it = myLocation.getIndexes().begin();
				for (size_t i = 2; i < myLocation.getIndexes().size(); i++, it++)
				{
					file = myLocation.getPath() + "/" + *it;
					cgi(file);
				}
			}else{
				it = myLocation.getIndexes().begin();
				for (size_t i = 0; i < 2; i++, it++)
				{
					file = myLocation.getPath() + "/" + *it;
					cgi(file);


				}
			}
		}else if(myLocation.getListingDir() == "on"){
			listing_dir(fd, myLocation);
		}
		else
			throw errorMessage(403, box.getClients()[fd].getServerId());
	}


	// std::cout << "GET method - :" << std::endl;
	// std::cout << box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation().at(ind).getPath() << std::endl;
	// std::cout << reqPath << "--------" << file << std::endl;

}



