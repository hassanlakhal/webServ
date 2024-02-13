/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:04:20 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/13 18:19:01 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"webServer.hpp"

webServer::webServer(const std::string& nameFile) : nameFile(nameFile)
{
}

webServer::webServer()
{
}

webServer::webServer(const webServer& other)
{
    this->servers = other.servers;
}

webServer& webServer::operator=(const webServer& other)
{
    if (this != &other)
    {
        this->servers = other.servers;
    }
    return *this;
}

void webServer::loadLocation()
{
}

void webServer::addServer(Server *s)
{
    servers.push_back(*s);
}

Server* webServer::createServer()
{
    Server *a = new Server;
    return a;
}

std::vector<Server> webServer::getServer() const
{
    return this->servers;
}

void webServer::loadConfigFile()
{
}

webServer::~webServer()
{
}
