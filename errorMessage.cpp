/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:25:10 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/23 02:40:22 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"errorMessage.hpp"
#include"parsingFile.hpp"
errorMessage::errorMessage()
{

}

errorMessage::errorMessage(int status ,std::string& path ,bool isCgi) throw()
{
    std::ostringstream oss;
    oss << path;
    if (!isCgi)
    {
        this->type = "text/html";
        this->body =  oss.str();
    }
    else
        this->message = oss.str();
    this->status_code = status;
    this->isCgi = isCgi;
}

errorMessage::errorMessage(int status, std::string& path, std::string& type) throw()
{
    std::ostringstream oss, os;
    this->isCgi = false;
    oss << path;
    os << type;
    this->status_code = status;
    this->type = os.str();
    this->message = oss.str();
}

const std::string& errorMessage::getType() const
{
    return type;
}

bool errorMessage::getCgiStatus() const
{
    return this->isCgi;
}

errorMessage::errorMessage(int status, int ind, int posLocation) throw()
{
    webServer wserv = getMyServer();
    this->isCgi = false;
    std::ostringstream oss;
    if (status == 301)
    {
        this->status_code = status;
        oss << wserv.getServer()[ind].getLocation()[posLocation].getRedirect();
    }
    this->message = oss.str();
    this->type = "text/html";
}

int errorMessage::getStatusCode() const
{
    return this->status_code;
}

const std::string& errorMessage::getBody() const
{
    return this->body;
}

errorMessage::errorMessage(int status, int ind, const std::string& type) throw()
{
    webServer wserv = getMyServer();
    this->isCgi = false;
    this->error =  wserv.getServer()[ind].getErrorPath();
    std::ostringstream oss;
    std::map<int ,std::string>::iterator it = error.find(status);
    if (it != error.end())
        oss << it->second;
    this->status_code = status;
    this->type = type;
    this->message = oss.str();
}

const char* errorMessage::what() const throw()
{
    return this->message.c_str();
}

errorMessage::~errorMessage() throw()
{

}
