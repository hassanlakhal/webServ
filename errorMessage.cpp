/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:25:10 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/20 22:37:25 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"errorMessage.hpp"

errorMessage::errorMessage()
{
    
}

errorMessage::errorMessage(int lineNumber, const std::string& message) throw() 
{
    std::ostringstream oss;
    if (lineNumber == 404)
        oss << message;
    this->message = oss.str();
}

const char* errorMessage::what() const throw() 
{
    return this->message.c_str();
}

errorMessage::~errorMessage() throw()
{
    
}