/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:30 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/18 23:28:23 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"

Client::Client(): loadingHead(true) 
{
}

Client::~Client()
{
}

const Client& Client::getClinet() const
{
    return *this;
}

void Client::setRequset(std::string& buff)
{
    fullRequset.append(buff);
    // std::cout << fullRequset << std::endl;
}

const std::string& Client::getRequset() const
{
    return this->fullRequset;
} 

const std::string& Client::getMethod() const
{
    // std::cout << method << std::endl;
    return this->method;
}

void Client::setStartLine(std::istringstream& iss)
{
    getline(iss,method,' ');
    getline(iss,path,' ');
    getline(iss,protocal, '\n');
}

void Client::loadingFormation(std::string& line)
{
    std::istringstream iss(line);
    std::string key ,value;
    long nb;
    while (getline(iss, key,':') && getline(iss,value))
    {
        std::cout << key << " ===== "<<  value << "\n";
        if (key == "host")
            this->host = value;
        if (key == "Transfer-Encoding" && value != "chunked")
            throw std::runtime_error("error 501");
        if(method == "POST" && key == "Content-Length")
        {
            std::istringstream v(value);
            v >> nb;
            if (nb == 0)
                throw std::runtime_error("error 400");
        }
        if (path.find("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~!$&'()*+,;=") != std::string::npos)
            throw std::runtime_error("error 404");
        if (host.length() + path.length() > 20)
             throw std::runtime_error("error 414");
        
    }
        
}

void Client::ParsingRequest()
{
    std::istringstream iss(this->fullRequset);
    std::string line;
    if (loadingHead)
    {
        setStartLine(iss);
        std::cout << "----header: ----" << std::endl;
        while (getline(iss, line) && getline(iss, line, '\r') && !line.empty())
        {
            loadingFormation(line);
            // std::cout << line << std::endl;
        }
        // std::cout << method << " ";
        // std::cout << path << " ";
        // std::cout << protocal << std::endl; 
        loadingHead = false;
    }
}