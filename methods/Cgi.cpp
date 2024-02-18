/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:29 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/18 22:55:49 by eej-jama         ###   ########.fr       */
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
		if(extention == it->first){
			return it->second;
		}
	}
	return "text";
}


int cgi(Box& box, Location& myLocation, int fd, std::string reqPath, std::string file, int serverID, std::string method, std::string postFile){
	std::string extention = "";
	char cgi_path[PATH_MAX];
	char current_path[PATH_MAX];
	char root_path[PATH_MAX];
	if(file.find('.') != std::string::npos)
		extention = file.substr(file.find('.') + 1);
	bool cgiExist = false;
	std::string tem;
	std::string fileDel;

	realpath(reqPath.c_str(), cgi_path);
	std::string sd(cgi_path);
	realpath(".", current_path);
	std::string sc(current_path);
	realpath(myLocation.getRoot().c_str(), root_path);
	std::string sr(root_path);
	if(sd.find(sc) == std::string::npos || sd.find(sr) == std::string::npos)
		throw errorMessage(403, serverID);

//--------------------
	FILE * tmpfile = std::fopen((reqPath).c_str(), "r");
	if(!tmpfile){
		return 0;
	}
	else
		std::fclose(tmpfile);
	if(!myLocation.getCgiPath().size() && method == "GET")
	{
		std::string formatType = fillMapType(extention);
		std::string tem = formatType + "/" + extention;
		throw errorMessage(200,  reqPath, tem);
	}
	else if(!myLocation.getCgiPath().size() && method == "POST")
	{
		if(method == "POST"){
			if(unlink(postFile.c_str()) == -1)
				throw errorMessage(500, serverID);
		}
		throw errorMessage(403, serverID);
	}
	else
	{
		if(!box.getClients()[fd].getDetectCgi()){
			std::map<std::string, std::string>::const_iterator it;
			it = myLocation.getCgiPath().begin();
			for (; it != myLocation.getCgiPath().end(); it++)
			{
				if(it->first == "." + extention)
				{
					cgiExist = true;
					box.getClients()[fd].setDetectCgi(true);
					std::string line;
					int status;
					FILE* outfile;
					std::stringstream iss;
					iss << "outfile_";
					iss << box.getClients()[fd].getIncremetedFileName();
					box.getClients()[fd].IncremetedFileName();
					iss << "_";
					iss << time(0);
					fileDel = iss.str();
					outfile = std::fopen(fileDel.c_str(), "w");
					if(!outfile)
						throw errorMessage(500, serverID);

					clock_t start_time;
					start_time = clock();
					box.getClients()[fd].setPidChild(fork());
					int pid = box.getClients()[fd].getPidChild();
					if(pid == 0){

						FILE* infilePost = NULL;
						if(method == "POST"){
							infilePost = std::fopen(postFile.c_str(), "r");
							if(!infilePost){
								kill(pid, SIGKILL);
								waitpid(pid, &status,0);
								throw errorMessage(500, serverID);
							}
						}
						std::string arg2 = reqPath;
						char *arg[] = {(char*)it->second.c_str(), (char*)(arg2.c_str()), NULL};

						if(dup2(fileno(outfile), 1) == -1)
							perror("dup2 fail ");
						std::fclose(outfile);

						if(method == "POST")
						{
							if(dup2(fileno(infilePost), 0) == -1)
								perror("dup2-- fail ");
							std::fclose(infilePost);
						}

						std::map<std::string, std::string> mapInfo = box.getClients()[fd].getInfoMap();
						std::string a = "CONTENT_LENGTH=" + mapInfo["Content-Length"];
						std::string b = "CONTENT_TYPE=" + mapInfo["Content-Type"];
						std::string c = "PATH_TRANSLATED=" + arg2;
						std::string d = "REQUEST_METHOD=" + box.getClients()[fd].getMethod();
						std::string e = "QUERY_STRING=" + box.getQueryString();
						std::string g = "HTTP_COOKIE=" + mapInfo["Cookie"];
						std::string f = "REDIRECT_STATUS=CGI";

						char *env[]= {
							(char *)a.c_str(),
							(char *)b.c_str(),
							(char *)c.c_str(),
							(char *)d.c_str(),
							(char *)e.c_str(),
							(char *)f.c_str(),
							(char *)g.c_str(),
						};

						execve(arg[0],arg , env);
						exit(48);
					}

					std::fclose(outfile);
					box.getClients()[fd].setStatusChild(status);
			}
				// while(1){
				int status = box.getClients()[fd].getStatusChild();
				if (waitpid(box.getClients()[fd].getPidChild(), &status, WNOHANG) == 0)
					throw 1;
				box.getClients()[fd].setDetectCgi(false);

					// if(clock() - start_time > 5000000){
					// 	kill(pid, SIGKILL);
					// 	waitpid(pid, &status,0);
					// 	if(unlink(fileDel.c_str()) == -1)
					// 		throw errorMessage(500, serverID);
					// 	throw errorMessage(504, serverID);
					// }
				// }

				if(WEXITSTATUS(status) != 0){
					std::cout << "status : " << WEXITSTATUS(status) << std::endl;
					if(unlink(fileDel.c_str()) == -1)
						throw errorMessage(500, serverID);
					throw errorMessage(500, serverID);
					std::cout << "status : " <<WEXITSTATUS(status) << "\n";
				}
				if(method == "POST"){
					if(unlink(postFile.c_str()) == -1)
						throw errorMessage(500, serverID);
				}
				throw errorMessage(200, fileDel,true);
			}
		}
		if(!cgiExist)
		{
			if(method == "POST"){
				unlink(postFile.c_str());
				throw errorMessage(500, serverID);
			}
			std::string formatType = fillMapType(extention);
			std::string tmpFile = reqPath ;
			std::ifstream file1(tmpFile.c_str());
			if (file1.is_open()){
				std::string tem = formatType + "/" + extention;
				throw errorMessage(200, tmpFile, tem);
			}
			throw errorMessage(404,serverID);
		}
	}
	return 1;
}
