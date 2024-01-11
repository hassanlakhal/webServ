/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/11 02:14:43 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"


Server::Server()
{
}

Server::~Server()
{
}

void Server::addLocation(Location *location)
{
   std::cout << location->getPath() << std::endl;
    Locations.push_back(*location);
    printf("%p\n",location);
}

Server* Server::createServer()
{
    Server *newServer = new Server;
    return newServer;
}

void Server::setListen(std::string& listen)
{
    if (listen[0] != ' ')
        throw std::runtime_error("error line listen");
    std::istringstream iss(listen);
    long nb;
    iss >> nb;
    this->listen = nb;
    // this->listen = listen;
}

long Server::getListen() const
{
    return this->listen;
}

void Server::setHost(std::string& host)
{
    (void)host;
    this->host =  host;
}

std::string Server::getHost() const
{
    return host;
}
void Server::setRoot(std::string& root)
{
    // std::cout << root << std::endl;
    this->root =  root;
}

std::string Server::getRoot() const
{
    return root;
}

const std::vector<Location>& Server::getLocation() const
{
    return this->Locations;
}

void Server::setMaxBodySize(std::string& maxBodySize)
{
    (void)maxBodySize;
    // this->client_max_body_size = maxBodySize;
}