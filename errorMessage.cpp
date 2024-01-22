/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:25:10 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/22 16:01:09 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"errorMessage.hpp"
#include"parsingFile.hpp"
errorMessage::errorMessage()
{
    
}

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