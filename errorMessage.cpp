/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:25:10 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/25 20:44:36 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"errorMessage.hpp"
#include"parsingFile.hpp"
errorMessage::errorMessage()
{
    
}

errorMessage::errorMessage(int status, int ind, int posLocation) throw()
{
    webServer wserv = getMyServer();
    std::ostringstream oss;
    if (status == 301)
    {
        this->status_code = status;
        oss << wserv.getServer()[ind].getLocation()[posLocation].getRediract();
    }
    this->message = oss.str();
}

int errorMessage::getStatusCode() const
{
    return this->status_code;
}
errorMessage::errorMessage(int status, int ind) throw() 
{
    webServer wserv = getMyServer();
    this->error =  wserv.getServer()[ind].getErrorPath();
    std::ostringstream oss;
    std::map<int ,std::string>::iterator it = error.find(status);
    if (it != error.end())
        oss << it->second;
    this->status_code = status;
    this->message = oss.str();
}

const char* errorMessage::what() const throw() 
{
    return this->message.c_str();
}

errorMessage::~errorMessage() throw()
{
    
}