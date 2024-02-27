/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:15 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/27 16:15:05 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "methods.hpp"

void post(Box &box, int ind, int fd){
	std::vector<unsigned char> body = box.getClients()[fd].getBody();
	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	int serverID = box.getClients()[fd].getServerId();
	std::string reqPath = box.getClients()[fd].getPath();
	char post_path[PATH_MAX];
	char current_path[PATH_MAX];
	char root_path[PATH_MAX];
	reqPath = box.removeSlach(reqPath);
	reqPath =box.getClients()[fd].FullQueryString(reqPath);
	std::string file = reqPath;
	reqPath = reqPath.substr(1);
	struct stat oStat;
	if(stat(reqPath.c_str(), &oStat) != 0)
		throw errorMessage(404, serverID);
	if(!S_ISDIR(oStat.st_mode)){
		file = file.substr(file.find_last_of('/') + 1);
	}
	else
		file = "";

	realpath(reqPath.c_str(), post_path);
	std::string sd(post_path);
	realpath(".", current_path);
	std::string sc(current_path);
	realpath(myLocation.getRoot().c_str(), root_path);
	std::string sr(root_path);
	if(sd.find(sc) == std::string::npos || sd.find(sr) == std::string::npos)
		throw errorMessage(403, serverID);
	if(box.getClients()[fd].getInfoMap()["Content-Type"].find("boundary") != std::string::npos)
		throw errorMessage(501, serverID);
	if(file.empty() && myLocation.getUpload() == "off"){
		throw errorMessage(403, serverID);
	}else{
		std::map<std::string, std::string> mapInfo = box.getClients()[fd].getInfoMap();
		std::string filePath, extention = mapInfo["Content-Type"].substr(mapInfo["Content-Type"].find("/") + 1);
		if(mapInfo["Transfer-Encoding"].empty()){
			if(!box.getClients()[fd].getOutFileOpened()){
				std::stringstream iss;
				struct stat mStat;
				std::string pa =  myLocation.getRoot() + "/" + myLocation.getUploadPath();
				if((myLocation.getUploadPath().empty() || stat(pa.c_str(), &mStat) != 0) && file.empty()){
					throw errorMessage(500, serverID);
				}
				if(myLocation.getUploadPath().empty() || stat(pa.c_str(), &mStat) != 0){
					iss << myLocation.getRoot();
				}
				else
					iss << myLocation.getRoot() + "/" + myLocation.getUploadPath();
				iss << "/file_";
				iss << time(0);
				iss << "_";
				iss << box.getClients()[fd].getIncremetedFileName();
				iss << ".";
				iss << extention;
				filePath = iss.str();

				box.getClients()[fd].openFile(filePath);
				box.getClients()[fd].IncremetedFileName();
			}
			fwrite(&body[0], 1, body.size(), box.getClients()[fd].getOutFile());
			std::istringstream iss(mapInfo["Content-Length"].c_str());
			size_t nb;
			iss >> nb;
			if(box.getClients()[fd].getSizeBody() >= nb){
				box.getClients()[fd].setOutFileOpened(false);
				fclose(box.getClients()[fd].getOutFile());
				body.clear();
				if(!file.empty()){
					if(cgi(box.getClients()[fd], myLocation, reqPath, file, serverID, "POST", box.getClients()[fd].getFilePath())){
					}
					else
						throw errorMessage(404, serverID);
				}
				else{
					std::string path_page = "error_page/201.html";
					std::string type = "text/html";
					throw errorMessage(201,path_page,type);
				}
			}
		}
		else if(mapInfo["Transfer-Encoding"] == "chunked"){
			std::string to_write;
			if(!box.getClients()[fd].getOutFileOpened()){
				std::stringstream iss;
				struct stat mStat;
				std::string pa =  myLocation.getRoot() + "/" + myLocation.getUploadPath();
				if((myLocation.getUploadPath().empty() || stat(pa.c_str(), &mStat) != 0) && file.empty()){
					throw errorMessage(500, serverID);
				}
				if(myLocation.getUploadPath().empty() || stat(pa.c_str(), &mStat) != 0){
					iss << myLocation.getRoot();
				}
				else
					iss << myLocation.getRoot() + "/" + myLocation.getUploadPath();
				iss << "/file_";
				iss << time(0);
				iss << "_";
				iss << box.getClients()[fd].getIncremetedFileName();
				box.getClients()[fd].IncremetedFileName();
				iss << ".";
				iss << extention;
				filePath = iss.str();
				box.getClients()[fd].openFile(filePath);
			}
			std::vector<unsigned char>::iterator it;
			std::string strBody(body.begin(), body.end());
			if(strBody.length()){
				std::string chunk = strBody;
				if(!box.getClients()[fd].getEnteredfirstTime()){
					strBody =  box.getClients()[fd].getStringBody() + strBody;
					std::string chunkSize = strBody.substr(0, strBody.find("\r\n"));
					if(chunkSize == "0"){
						body.clear();
						box.getClients()[fd].setOutFileOpened(false);
						box.getClients()[fd].setStringBody('e', "");
						fclose(box.getClients()[fd].getOutFile());
						if(box.getClients()[fd].getSizeCompared() > box.getWebServer().getServer()[serverID].getMaxBodySize()){
							unlink(filePath.c_str());
							throw errorMessage(413, serverID);
						}
						if(!file.empty()){
							if(cgi(box.getClients()[fd], myLocation, reqPath, file, serverID, "POST", box.getClients()[fd].getFilePath())){

							}
							else
								throw errorMessage(404, serverID);
						}
						else{
							std::string path_page = "error_page/201.html";
							std::string type = "text/html";
							throw errorMessage(201,path_page,type);
						}
					}
					box.getClients()[fd].setChunkSizee(strtoul(chunkSize.c_str(), NULL, 16));
					chunk = strBody.substr(strBody.find("\r\n") + 2);

					box.getClients()[fd].setSizeAppended('a', chunk.length());
					box.getClients()[fd].setStringBody('e', chunk);
					box.getClients()[fd].setEnteredfirstTime(true);
				}else{

					box.getClients()[fd].setSizeAppended('a', chunk.length());
					box.getClients()[fd].setStringBody('a', chunk);
				}
				if(box.getClients()[fd].getChunkSizee() <= box.getClients()[fd].getSizeAppended()){
					to_write = box.getClients()[fd].getStringBody();
					box.getClients()[fd].setStringBody('e', box.getClients()[fd].getStringBody().substr(box.getClients()[fd].getChunkSizee()));

					to_write = to_write.substr(0, box.getClients()[fd].getChunkSizee());
					fwrite(to_write.c_str(), 1, to_write.length(), box.getClients()[fd].getOutFile());
					box.getClients()[fd].setEnteredfirstTime(false);
					box.getClients()[fd].setSizeAppended('e', 0);
					box.getClients()[fd].setSizeCompared(to_write.length());
					if(box.getClients()[fd].getSizeCompared() > box.getWebServer().getServer()[serverID].getMaxBodySize()){
						fclose(box.getClients()[fd].getOutFile());
						unlink(filePath.c_str());
						throw errorMessage(413, serverID);
					}
					if(box.getClients()[fd].getStringBody().find("\r\n0\r\n") != std::string::npos){
						box.getClients()[fd].setOutFileOpened(false);
						box.getClients()[fd].setStringBody('e', "");
						body.clear();
						fclose(box.getClients()[fd].getOutFile());
						if(!file.empty()){
							if(cgi(box.getClients()[fd], myLocation, reqPath, file, serverID, "POST", filePath)){

							}
							else
								throw errorMessage(404, serverID);
						}
						else{
							std::string path_page = "error_page/201.html";
							std::string type = "text/html";
							throw errorMessage(201,path_page,type);
						}
					}
				}
			}
		}

	}
}

