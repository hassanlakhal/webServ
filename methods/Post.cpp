/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:15 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/12 17:02:05 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"

void post(Box &box, int ind, int fd){
	std::vector<unsigned char> body = box.getClients()[fd].getBody();
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

	if(file.empty() && myLocation.getUpload() == "off"){
		throw errorMessage(403, serverID);
	}else{
		std::map<std::string, std::string> mapInfo = box.getClients()[fd].getInfoMap();
		std::string filePath, extention = mapInfo["Content-Type"].substr(mapInfo["Content-Type"].find("/") + 1);
		if(mapInfo["Transfer-Encoding"].empty()){
			if(!box.getClients()[fd].getOutFileOpened()){
				std::cout << "oppopopopopopopopopop\n";
				int status = std::system(("mkdir -p " + myLocation.getRoot() + "/" + myLocation.getUploadPath()).c_str());
				if(status != 0)
					throw errorMessage(500, serverID);
				std::stringstream iss;
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
				//throw

			fwrite(&body[0], 1, body.size(), box.getClients()[fd].getOutFile());
			std::cout << "size body : " << box.getClients()[fd].getSizeBody() << std::endl;
			std::cout << "Content-Length : " << static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str())) << std::endl;
			if(box.getClients()[fd].getSizeBody() >= static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str()))){

				box.getClients()[fd].setOutFileOpened(false);
				// box.getClients()[fd].getOutFile().close();
				fclose(box.getClients()[fd].getOutFile());
				body.clear();
				if(!file.empty()){
					std::cout << "ccPath : " << reqPath << "\n";
					if(cgi(box, myLocation, fd, reqPath, file, serverID, "POST", box.getClients()[fd].getFilePath())){
					}
					else
						throw errorMessage(404, serverID);
				}
				else{
					std::string path_page = "error_page/201.html";
					std::string type = "txt/html";
					throw errorMessage(201,path_page,type);
				}
			}
		}
		else if(mapInfo["Transfer-Encoding"] == "chunked"){
			std::string to_write;
			if(!box.getClients()[fd].getOutFileOpened()){
				int status = std::system(("mkdir -p " + myLocation.getRoot() + "/" + myLocation.getUploadPath()).c_str());
				if(status != 0)
					throw errorMessage(500, serverID);
				std::stringstream iss;
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
			else
				//throw
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
						// box.getClients()[fd].getOutFile().close();
						fclose(box.getClients()[fd].getOutFile());
						// box.getClients()[fd]
						if(!file.empty()){
							if(cgi(box, myLocation, fd, reqPath, file, serverID, "POST", box.getClients()[fd].getFilePath())){

							}
							else
								throw errorMessage(404, serverID);
						}
						else{
							std::string path_page = "error_page/201.html";
							std::string type = "txt/html";
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
					// box.getClients()[fd].getOutFile().write(to_write.c_str(), box.getClients()[fd].getChunkSizee());
					fwrite(to_write.c_str(), 1, to_write.length(), box.getClients()[fd].getOutFile());
					box.getClients()[fd].setEnteredfirstTime(false);
					box.getClients()[fd].setSizeAppended('e', 0);
					if(box.getClients()[fd].getStringBody().find("\r\n0\r\n") != std::string::npos){
						box.getClients()[fd].setOutFileOpened(false);
						box.getClients()[fd].setStringBody('e', "");
						body.clear();
						// box.getClients()[fd].getOutFile().close();
						fclose(box.getClients()[fd].getOutFile());
						if(!file.empty()){
							if(cgi(box, myLocation, fd, reqPath, file, serverID, "POST", filePath)){

							}
							else
								throw errorMessage(404, serverID);
						}
						else{
							std::string path_page = "error_page/201.html";
							std::string type = "txt/html";
							throw errorMessage(201,path_page,type);
						}
					}
				}
			}
		}

	}
}

