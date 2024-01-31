/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:06:29 by eej-jama          #+#    #+#             */
/*   Updated: 2024/01/31 22:18:30 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"


void cgi(Location& myLocation, std::string reqPath, std::string file, int serverID){
	std::cout << "path : " << reqPath << "-------" << file << "------" << file.substr(file.find('.') + 1) << std::endl;
	std::string extention = file.substr(file.find('.'));
	bool cgiExist = false;
	std::string tem;
	std::string fileDel;
	if(!myLocation.getCgiPath().size())
	{
		tem = "text/" + extention.substr(1);
		throw errorMessage(200, reqPath, tem);
	}
	else{
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
					std::cout << "test" << std::endl;
					throw errorMessage(500, serverID);
				}
				clock_t start_time;
				start_time = clock();
				int pid = fork();

				if(pid == 0){
					std::cout << "fffffff" << fileno(outfile) << std::endl;
					if(dup2(fileno(outfile), 1) == -1)
						perror("dup2 fail ");
					char *arg[] = {(char*)it->second.c_str(), (char*)reqPath.c_str(), NULL};
					execve(arg[0],arg , NULL);
					exit(48);
				}
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
				std::fclose(outfile);
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
			std::string temp = "text/html";
			std::ifstream file(reqPath.c_str());
			if (file.is_open())
				throw errorMessage(200, reqPath, temp);
			throw errorMessage(404,serverID);
		}

	}
}
