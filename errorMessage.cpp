/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:25:10 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/21 22:18:09 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"errorMessage.hpp"
#include"parsingFile.hpp"
errorMessage::errorMessage()
{
    
}

// void errorMessage::setServer(Server& server)
// {
//     webServer wserv = getMyServer();
//     this->error = server.getErrorPath();
//     std::cout << "Number of elements in map: " << error.size() << std::endl;
//     for (std::map<int, std::string>::iterator it = error.begin(); it != error.end(); ++it) {
//         std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
//     }
//     std::cout << "Test key 400: " << error[400] << std::endl;
// }

// errorMessage::errorMessage(int lineNumber, const std::string& message) throw() 
// {
//     webServer wserv = getMyServer();
//     std::cout << << wserv.getServer()[0].getRoot() << std::endl;
//     std::ostringstream oss;
//     if (lineNumber == 404)
//         oss << message;
//     this->message = oss.str();
// }

errorMessage::errorMessage(int status, int ind) throw() 
{
    webServer wserv = getMyServer();
    this->error =  wserv.getServer()[ind].getErrorPath();
    std::ostringstream oss;
    std::map<int ,std::string>::iterator it = error.find(status);
    if (it != error.end())
        oss << it->second;
    this->message = oss.str();
}

const char* errorMessage::what() const throw() 
{
    return this->message.c_str();
}

errorMessage::~errorMessage() throw()
{
    
}