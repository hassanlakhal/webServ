/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:29 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/27 16:50:28 by eej-jama         ###   ########.fr       */
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


int cgi(Client& client, Location& myLocation, std::string reqPath, std::string file, int serverID, std::string method, std::string postFile){

	std::string extention = "";
	char cgi_path[PATH_MAX] = {0};
	char current_path[PATH_MAX] = {0};
	char root_path[PATH_MAX] = {0};
	if(file.find('.') != std::string::npos)
		extention = file.substr(file.find('.') + 1);
	bool cgiExist = false;
	std::string tem;
	std::string fileDel;

	if(!client.getDetectCgi())
	{
		client.setLocation(myLocation);
		client.setSavedReqPath(reqPath);
		client.setSavedFile(file);
		client.setSavedServerID(serverID);
		client.setSavedMethod(method);
		client.setSavedPostFIle(postFile);
		realpath(reqPath.c_str(), cgi_path);
		std::string sd(cgi_path);
		realpath(".", current_path);
		std::string sc(current_path);
		realpath(myLocation.getRoot().c_str(), root_path);
		std::string sr(root_path);
		if(sd.find(sc) == std::string::npos || sd.find(sr) == std::string::npos)
			throw errorMessage(403, serverID);
		FILE * tmpfile = std::fopen((reqPath).c_str(), "r");
		if(!tmpfile){
			return 0;
		}
		else
			std::fclose(tmpfile);
	}

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
		std::map<std::string, std::string>::const_iterator it;
		it = myLocation.getCgiPath().begin();
		for (; it != myLocation.getCgiPath().end(); it++)
		{
			if(it->first == "." + extention)
			{
				cgiExist = true;
				if(!client.getDetectCgi()){
					client.setDetectCgi(true);
					std::string line;
					FILE* outfile;
					std::stringstream iss;
					iss << "outfile_";
					iss << client.getIncremetedFileName();
					client.IncremetedFileName();
					iss << "_";
					iss << time(0);
					fileDel = iss.str();
					client.setSavedDileDel(fileDel);
					outfile = std::fopen(fileDel.c_str(), "w");
					if(!outfile)
						throw errorMessage(500, serverID);
					int status;
					clock_t start_time;
					start_time = clock();
					client.setStartTimeCGI(start_time);
					client.setPidChild(fork());
					int pid = client.getPidChild();
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
						std::string arg2 = reqPath.substr(reqPath.rfind("/") + 1);
						// rado 4iiir smaya dyal file
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

						std::map<std::string, std::string> mapInfo = client.getInfoMap();
						std::string a = "CONTENT_LENGTH=" + mapInfo["Content-Length"];
						std::string b = "CONTENT_TYPE=" + mapInfo["Content-Type"];
						std::string c = "PATH_TRANSLATED=" + arg2;
						std::string d = "REQUEST_METHOD=" + client.getMethod();
						std::string e = "QUERY_STRING=" + client.getQueryString();
						std::string f = "REDIRECT_STATUS=CGI";
						std::string g = "HTTP_COOKIE=" + mapInfo["Cookie"];
						std::string h = "PATH_INFO=" + client.getPathInfo() ;

						char *env[]= {
							(char *)a.c_str(),
							(char *)b.c_str(),
							(char *)c.c_str(),
							(char *)d.c_str(),
							(char *)e.c_str(),
							(char *)f.c_str(),
							(char *)g.c_str(),
							(char *)h.c_str(),
							NULL
						};
						if(reqPath.find("/") != std::string::npos){
							std::string newD = reqPath.substr(0, reqPath.rfind("/"));
							chdir(newD.c_str());
 						}

						execve(arg[0],arg , env);
						exit(48);
					}

					std::fclose(outfile);
				}
				int status ;
				int serverID= client.getSavedServerID();
				fileDel = client.getSavedFileDel();
				clock_t endTime = clock();
				if (endTime - client.getStartTimeCGI() >= 5000000 )
				{
					client.setDetectCgi(false);
					kill(client.getPidChild(), SIGKILL);
					waitpid(client.getPidChild(), &status,0);
					if(unlink(fileDel.c_str()) == -1)
						throw errorMessage(500, serverID);
					throw errorMessage(504, serverID);
				}
				else if (waitpid(client.getPidChild(), &status, WNOHANG) == 0){
					return 1;
				}
				client.setDetectCgi(false);
				if(WEXITSTATUS(status) != 0){
					if(unlink(fileDel.c_str()) == -1)
						throw errorMessage(500, serverID);
					throw errorMessage(500, serverID);
				}
				if(method == "POST"){
					postFile = client.getSavedPostFIle();
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
