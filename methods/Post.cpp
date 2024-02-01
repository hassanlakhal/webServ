/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:08:15 by eej-jama          #+#    #+#             */
/*   Updated: 2024/02/01 18:17:06 by eej-jama         ###   ########.fr       */
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
	std::cout << "post method" << std::endl;
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
				box.getClients()[fd].openFile(filePath);
			}
			else
				//throw
			std::cout << "fd : " << fileno(box.getClients()[fd].getOutFile()) << std::endl;
			std::cout << "extention : " << extention << std::endl;
			// std::string contentFile;
			// write(fileno(outfile), , )

			static size_t size;
			size += body.size();
			std::cout << "size : " << size << std::endl;
			// fwrite(&(bodyString.c_str())[0], sizeof(char), bodyString.size(), box.getClients()[fd].getOutFile());
			fwrite(&body[0], sizeof(char), body.size(), box.getClients()[fd].getOutFile());
			if(size == static_cast<size_t>(atoi(mapInfo["Content-Length"].c_str()))){

				std::cout << "vvvvvvvvvvvvvvvvvvvvvvvv" << std::endl;
				std::fclose(box.getClients()[fd].getOutFile());
			}
		}
		else if(mapInfo["Transfer-Encoding"] == "chunked"){

		}
	}
}
