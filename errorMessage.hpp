/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/31 11:05:28 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ERROR_MESSAGE_HPP
#define ERROR_MESSAGE_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>
#include<map>
// #include"Server.hpp"
class errorMessage : public std::exception 
{
    public:
        errorMessage();
        errorMessage(int status, std::string& body) throw();
        errorMessage(int status, std::string& path, std::string& type) throw();
        errorMessage(int status, int ind, const std::string& type = "text/html") throw();
        errorMessage(int status, int ind, int posLocation) throw();
        int getStatusCode() const;
        const std::string& getType() const;
        const std::string& getBody() const;
        virtual const char* what() const throw();
        virtual ~errorMessage() throw();

    protected:
        std::string message;
        int status_code;
        std::string type;
        std::string body;
        std::map<int, std::string> error;
};
#endif