/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/09 16:59:38 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"


Server::Server()
{
}

Server::~Server()
{
}

void Server::addLocation(Location& location)
{
    Locations.push_back(location);
}

Server* Server::createServer()
{
    Server *newServer = new Server;
    return newServer;
}

void Server::setListen(std::string& listen)
{
    (void)listen;
    // this->listen = listen;
}

void Server::setHost(std::string& host)
{
    (void)host;
    // this->host =  host;
}

void Server::setRoot(std::string& root)
{
    std::cout << root << std::endl;
    // this->host =  host;
}

void Server::setMaxBodySize(std::string& maxBodySize)
{
    (void)maxBodySize;
    // this->client_max_body_size = maxBodySize;
}