/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:15 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/05 03:19:09 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"

void post(Box &box, int ind, int fd){
	std::vector<unsigned char> body = box.getClients()[fd].getBody();

	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	if(myLocation.getUpload() == "off"){
		//throw
	}else{
		std::map<std::string, std::string> mapInfo = box.getClients()[fd].getInfoMap();
		std::string filePath, extention = mapInfo["Content-Type"].substr(mapInfo["Content-Type"].find("/") + 1);
		if(mapInfo["Transfer-Encoding"].empty()){
			if(!box.getClients()[fd].getOutFileOpened()){
				std::cout <<  "ddddddddddddddddddddd" << std::endl;
				std::stringstream iss;
				iss << "upload/uploaded_file_";
				iss << time(0);
				iss << ".";
				iss << extention;
				filePath = iss.str();
			std::cout << "file path : " << filePath << std::endl;
				box.getClients()[fd].openFile(filePath);
			}
			else
				//throw
			std::cout << "extention : " << extention << std::endl;
			std::cout << "size : " << box.getClients()[fd].getSizeBody() << std::endl;
			std::cout << "size of body : " << body.size() << std::endl;
			std::cout << "test : " << static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str())) << std::endl;
			box.getClients()[fd].getOutFile().write(reinterpret_cast<char*>(body.data()), body.size());
			if(box.getClients()[fd].getSizeBody() == static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str()))){

				std::cout << "vvvvvvvvvvvvvvvvvvvvvvvv" << std::endl;
				box.getClients()[fd].setOutFileOpened(false);
				box.getClients()[fd].getOutFile().close();
				body.clear();
				std::string path_page = "error_page/201.html";
				std::string type = "txt/html";
				throw errorMessage(201,path_page,type);
			}
		}
		else if(mapInfo["Transfer-Encoding"] == "chunked"){
			std::string to_write;
			if(!box.getClients()[fd].getOutFileOpened()){
				std::stringstream iss;
				iss << "upload/uploaded_file_";
				iss << time(0);
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
						box.getClients()[fd].getOutFile().close();
						// box.getClients()[fd]
						std::string path_page = "error_page/201.html";
						std::string type = "txt/html";
						throw errorMessage(201,path_page,type);
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
					box.getClients()[fd].getOutFile().write(to_write.c_str(), box.getClients()[fd].getChunkSizee());
					box.getClients()[fd].setEnteredfirstTime(false);
					box.getClients()[fd].setSizeAppended('e', 0);
					if(box.getClients()[fd].getStringBody().find("\r\n0\r\n") != std::string::npos){
						box.getClients()[fd].setOutFileOpened(false);
						box.getClients()[fd].setStringBody('e', "");
						body.clear();
						box.getClients()[fd].getOutFile().close();
						std::string path_page = "error_page/201.html";
						std::string type = "txt/html";
						throw errorMessage(201,path_page,type);
					}
				}
			}
		}
	}
}

