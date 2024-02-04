/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:29 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/04 17:49:24 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"


std::string fillMapType(std::string extention){
	std::map<std::string, std::string> myMap;
	std::map<std::string, std::string>::iterator it;
	myMap["html"] = "text";
	myMap["htm"] = "text";
	myMap["csv"] = "text";
	myMap["css"] = "text";
	myMap["mp4"] = "video";
	myMap["mpeg"] = "video";
	myMap["png"] = "image";
	myMap["jpeg"] = "image";
	myMap["gif"] = "image";
	myMap["jpg"] = "image";
	myMap["aac"] = "audio";
	myMap["json"] = "application";
	myMap["x-www-form-urlencoded"] = "application";
	it = myMap.begin();
	for (; it != myMap.end(); it++)
	{
		if(extention == it->first)
			return it->second;
	}
	return "text";
}


int cgi(Location& myLocation, std::string reqPath, std::string file, int serverID){
	std::string extention = file.substr(file.find('.'));
	bool cgiExist = false;
	std::string tem;
	std::string fileDel;
	reqPath =  myLocation.getRoot() + "/" + reqPath;
	FILE * tmpfile = std::fopen((reqPath + "/" + file).c_str(), "r");
	if(!tmpfile){
		return 0;
	}
	else
		std::fclose(tmpfile);
	if(!myLocation.getCgiPath().size())
	{
		reqPath += "/" + file;
		std::string formatType = fillMapType(extention.substr(1));
		std::string tem = formatType + "/" + extention.substr(1);
		std::cout << "format type : " << tem <<std::endl;
		throw errorMessage(200, reqPath, tem);
	}
	else
	{

		std::map<std::string, std::string>::const_iterator it;
		it = myLocation.getCgiPath().begin();
		for (; it != myLocation.getCgiPath().end(); it++)
		{
			if(it->first == extention)
			{
				cgiExist = true;
				std::string line;
    			char buffer[BUFFER_SIZE] = {0};
				size_t size_read;
				int status;
				std::stringstream iss;
				iss << "outfile_";
				iss << time(0);
				fileDel = iss.str();
				FILE* outfile = std::fopen(fileDel.c_str(), "w");
				if(!outfile)
				{
					throw errorMessage(500, serverID);
				}

				clock_t start_time;
				start_time = clock();
				int pid = fork();

				if(pid == 0){
					std::cout << "fffffff" << fileno(outfile) << std::endl;
					std::string arg2 = reqPath + "/" + file;
					char *arg[] = {(char*)it->second.c_str(), (char*)(arg2.c_str()), NULL};
					std::cout << "arg[0] : " << arg[0] << std::endl;
					std::cout << "arg[1] : " << arg[1] << std::endl;
					if(dup2(fileno(outfile), 1) == -1)
						perror("dup2 fail ");
					execve(arg[0],arg , NULL);
					exit(48);
				}
				std::fclose(outfile);
				while(1){
					if (waitpid(pid, &status, WNOHANG) > 0)
						break;

					if(clock() - start_time > 5000000){
						kill(pid, SIGKILL);
						if(unlink(fileDel.c_str()) == -1)
							throw errorMessage(500, serverID);
						throw errorMessage(504, serverID);
					}
				}

				if(status != 0){
					if(unlink(fileDel.c_str()) == -1)
						throw errorMessage(500, serverID);
					throw errorMessage(500, serverID);
				}
				FILE* infile = std::fopen(fileDel.c_str(), "r");
				if(!infile){
					if(unlink(fileDel.c_str()) == -1)
						throw errorMessage(500, serverID);
					throw errorMessage(500, serverID);
				}
				std::string codeHTML = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title></head><body>";
				while ((size_read = read(fileno(infile), buffer, sizeof(buffer)))> 0)
				{
					codeHTML.append(buffer, size_read);
				}
				codeHTML += "</body></html>";
				std::fclose(infile);
				if(unlink(fileDel.c_str()) == -1)
					throw errorMessage(500, serverID);
				throw errorMessage(200, codeHTML);

			}
		}
		if(!cgiExist)
		{
			std::string formatType = fillMapType(extention);
			std::string tmpFile = reqPath + "/" + file;
	// std::cout << "fpath : " << reqPath << " file : " << tmpFile << std::endl;
			std::ifstream file(tmpFile.c_str());
			if (file.is_open()){
			{

				std::cout << "file to open : " << tmpFile << std::endl;
				std::string tem = formatType + "/" + extention.substr(1);
				std::cout << "format type : " << tem <<std::endl;
				throw errorMessage(200, tmpFile, tem);
			}

			}
			throw errorMessage(404,serverID);
		}

	}
	return 1;
}
