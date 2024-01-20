/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:30 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/20 15:47:29 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"

Client::Client(): loadingHead(true),serverId(0)
{
}

Client::Client(int serverId): loadingHead(true),serverId(serverId)
{
    
}

Client::~Client()
{
}

int Client::getServerId() const
{
    return this->serverId;
}

const Client& Client::getClinet() const
{
    return *this;
}

Client& Client::operator=(const Client& other) 
{
    if (this != &other) 
    {
        fullRequset = other.fullRequset;
        host = other.host;
        method = other.method;
        path = other.path;
        protocal = other.protocal;
        type = other.type;
        loadingHead = other.loadingHead;
        body = other.body;
        serverId = other.serverId;
    }
    return *this;
}

void Client::setRequset(std::string& buff)
{
    fullRequset.append(buff);
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
        if (key == "host")
            this->host = value;
        if(key == "Content-Type")
            this->type = value;
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

void Client::setBody(std::istringstream& buff)
{
    std::istreambuf_iterator<char> begin(buff);
    std::istreambuf_iterator<char> end;
    body.assign(begin,end);
}

const std::vector<unsigned char>& Client::getBody() const
{
    return this->body;
}

void Client::ParsingRequest()
{
    std::istringstream iss(this->fullRequset, std::ios::binary);
    std::string line;
    // std::cout << this->fullRequset.size() << std::endl;
    if (loadingHead)
    {
        setStartLine(iss);
        while (getline(iss, line) && getline(iss, line, '\r') && !line.empty())
        {
            loadingFormation(line);
        }
        setBody(iss);
        loadingHead = false;
    } 
}