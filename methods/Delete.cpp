/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:53 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/08 21:24:55 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"

bool check_empty(std::string path) {
    DIR* dir = opendir(path.c_str());
	std::cout << "the folder to be deleted : "<< path << "\n";
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

void remove_ressource(std::string file, std::string reqPath, int serverID){

	struct stat file_stat;


	if(!file.empty() && file != "." && file != "..")
	{
		if (stat(reqPath.c_str(), &file_stat) != 0)
			throw errorMessage(404, serverID);
		if(file_stat.st_mode & S_IWUSR){
			std::remove(reqPath.c_str());
		}
		else
			throw errorMessage(403, serverID);
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
				if(tmp.find('.') != std::string::npos){
					file = dent->d_name;
				}
				else
					file = "";
				remove_ressource(file, newReaPath, serverID);

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
			else{
				throw errorMessage(403, serverID);
			}

			closedir(dir);
		}
		else
			throw errorMessage(404, serverID);
	}
}

void deleteM(Box &box, int ind, int fd){
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	int serverID = box.getClients()[fd].getServerId();
	std::string reqPath = box.getClients()[fd].getPath();
	reqPath = box.removeSlach(reqPath);
	reqPath = box.FullQueryString(reqPath);
	reqPath = reqPath.substr(1);

	// std::cout << "my repath : " << reqPath << "\n";
	//clear the path
	std::string file;
	if(reqPath.find_last_of('/') != std::string::npos && reqPath.find('.') != std::string::npos)
		file = reqPath.substr(reqPath.find_last_of('/') + 1);
	else
		file = "";
	// std::cout << "my file : " << file << "\n";

	//check is I can remove the path
	// if(reqPath != myLocation.getRoot()){

	// }
	// else
		//throw you can't remove it
	remove_ressource(file, reqPath, serverID);
	// std::cout << "wsal hna\n";
	std::string path_page = "error_page/201.html";
	std::string type = "txt/html";
	throw errorMessage(201,path_page,type);

}
