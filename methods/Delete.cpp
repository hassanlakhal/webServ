/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:53 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/14 20:29:32 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"

bool check_empty(std::string path) {
    DIR* dir = opendir(path.c_str());
    if (dir == NULL)
        return false;

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_DIR && entry->d_name[0] != '.') {
            closedir(dir);
            return false;
        }
    }

    closedir(dir);
    return true;
}

void remove_ressource(std::string reqPath, int serverID){

	struct stat file_stat;

	if(stat(reqPath.c_str(), &file_stat) != 0)
		throw errorMessage(404, serverID);
	else
	{
		if(!S_ISDIR(file_stat.st_mode)){
			if(file_stat.st_mode & S_IWUSR)
				std::remove(reqPath.c_str());
		}
		else
		{
			DIR *dir;
			struct dirent *dent;
			if((dir = opendir(reqPath.c_str())) != NULL){

				while ((dent = readdir(dir)) != NULL)
				{
					std::string tmp(dent->d_name);
					if(tmp == "." || tmp == "..")
						continue;
					std::string newReaPath = reqPath + "/" + tmp;
					remove_ressource(newReaPath, serverID);
				}
				if(check_empty(reqPath.c_str())){
					if (stat(reqPath.c_str(), &file_stat) != 0)
						throw errorMessage(500, serverID);
					if(file_stat.st_mode & S_IWUSR){
						if (rmdir(reqPath.c_str()) != 0)
							throw errorMessage(500, serverID);
					}
					else
						throw errorMessage(403, serverID);
				}
				else
					throw errorMessage(403, serverID);
				closedir(dir);
			}
			else
				throw errorMessage(403, serverID);
		}
	}

}

void deleteM(Box &box, int ind, int fd){
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	int serverID = box.getClients()[fd].getServerId();
	char deleted_path[PATH_MAX];
	char current_path[PATH_MAX];
	char root_path[PATH_MAX];
	std::string reqPath = box.getClients()[fd].getPath();
	reqPath = box.removeSlach(reqPath);
	reqPath = box.FullQueryString(reqPath);
	reqPath = reqPath.substr(1);

	if (!realpath(reqPath.c_str(), deleted_path))
		throw errorMessage(404, serverID);
	std::string sd(deleted_path);
	if (!realpath(".", current_path))
		throw errorMessage(404, serverID);
	std::string sc(current_path);
	if (!realpath(myLocation.getRoot().c_str(), root_path))
		throw errorMessage(404, serverID);
	std::string sr(root_path);
	if(sd.find(sc) == std::string::npos || sr.length() >= sd.length())
		throw errorMessage(403, serverID);

	struct stat file_stat;

	if(stat(reqPath.c_str(), &file_stat) != 0)
		throw errorMessage(404, serverID);
	else
	{
		if(!S_ISDIR(file_stat.st_mode)){
			if(file_stat.st_mode & S_IWUSR)
				std::remove(reqPath.c_str());
			else
				throw errorMessage(403, serverID);
		}
		else
			remove_ressource(reqPath, serverID);
	}

	std::string path_page = "error_page/201.html";
	std::string type = "txt/html";
	throw errorMessage(201,path_page,type);

}
