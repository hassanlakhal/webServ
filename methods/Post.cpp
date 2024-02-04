/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:15 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/04 20:07:01 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "methods.hpp"

void post(Box &box, int ind, int fd){
	(void)box;
	(void)ind;
	(void)fd;
	// std::string fileUpld;
    // char buffer[BUFFER_SIZE] = {0};
	std::vector<unsigned char> body = box.getClients()[fd].getBody();
	// std::string bodyString = box.getClients()[fd].getStringBody();

	Location myLocation = box.getWebServer().getServer()[box.getClients()[fd].getServerId()].getLocation()[ind];
	// std::cout << "post method" << std::endl;
	if(myLocation.getUpload() == "off"){
		//throw
	}else{
		std::map<std::string, std::string> mapInfo = box.getClients()[fd].getInfoMap();
		std::string filePath, extention = mapInfo["Content-Type"].substr(mapInfo["Content-Type"].find("/") + 1);
		if(mapInfo["Transfer-Encoding"].empty()){
			if(!box.getClients()[fd].getOutFileOpened()){
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
			// std::cout << "fd : " << fileno(box.getClients()[fd].getOutFile()) << std::endl;
			std::cout << "extention : " << extention << std::endl;
			// std::string contentFile;
			// write(fileno(outfile), , )

			// static size_t size;
			if(!box.getClients()[fd].getOutFile())
			{
				exit(0);
			}
			// size += body.size();
			std::cout << "size : " << box.getClients()[fd].getSizeBody() << std::endl;
			std::cout << "size of body : " << body.size() << std::endl;
			std::cout << "test : " << static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str())) << std::endl;
			// fwrite(&(bodyString.c_str())[0], sizeof(char), bodyString.size(), box.getClients()[fd].getOutFile());
			// fwrite(&body[0], sizeof(char), body.size(), box.getClients()[fd].getOutFile());
			box.getClients()[fd].getOutFile().write(reinterpret_cast<char*>(body.data()), body.size());
			if(box.getClients()[fd].getSizeBody() == static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str()))){

				std::cout << "vvvvvvvvvvvvvvvvvvvvvvvv" << std::endl;
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
					box.getClients()[fd].setChunkSizee(strtoul(chunkSize.c_str(), NULL, 16));
					chunk = strBody.substr(strBody.find("\r\n") + 2);
					box.getClients()[fd].setSizeAppended(chunk.length());
					// std::cout << "chunk 1 : " << chunk << std::endl;
					box.getClients()[fd].setEnteredfirstTime(true);
					std::cout << "---------------------------------" << std::endl;
				}
				if(box.getClients()[fd].getChunkSizee() == box.getClients()[fd].getSizeAppended()){
					// std::cout << "body : " << box.getClients()[fd].getfullRequset() << std::endl;
					std::cout << "---------kkkkkkkkk------------------------" << std::endl;
					to_write = box.getClients()[fd].getStringBody() + chunk.substr(0, chunk.find("\r\n"));
					// std::cout << to_write << std::endl;
					// std::cout << to_write << std::endl;
					// std::cout << "---------------------------------" << std::endl;
					std::cout << "size of chunk : " << to_write.length() << std::endl;
					std::cout << "size chunk : " << box.getClients()[fd].getChunkSizee() << std::endl;
					// box.getClients()[fd].getOutFile().write(to_write.c_str(), box.getClients()[fd].getChunkSizee());
					// fwrite(to_write.c_str(), sizeof(char), box.getClients()[fd].getChunkSizee(), box.getClients()[fd].getOutFile());
					chunk.erase(0, chunk.find("\r\n") + 2);
					box.getClients()[fd].setStringBody('e', chunk);
					std::cout << "appended : |" << box.getClients()[fd].getStringBody().length() << "|" << std::endl;
					box.getClients()[fd].setEnteredfirstTime(false);
					// exit(0);
					// if(box.getClients()[fd].getSizeBody() == static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str()))){

					// 	box.getClients()[fd].getOutFile().close();
					// 	body.clear();
					// 	// throw errorMessage(301,box.getClients()[fd].getServerId(),ind);
					// }
				}
				else{
					std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
					std::cout << "size of chunk : " << chunk.length() << std::endl;
					box.getClients()[fd].setSizeAppended(chunk.length());
					box.getClients()[fd].setStringBody('a', chunk);
				}
				// std::cout << box.getClients()[fd].getStringBody() << std::endl;
			}
			// exit(0);




		}
	}
}

