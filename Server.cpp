/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/15 18:48:33 by hlakhal-         ###   ########.fr       */
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
    Locations.push_back(*location);
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

__int16_t Server::getListen() const
{
    return this->listen;
}

void Server::setHost(std::string& host)
{
    // (void)host;

    std::istringstream iss(host);
    std::string line;
    u_long number[4];
    int i = 0;
    while (getline(iss, line, '.') && i < 4)
    {
        if(line.length() > 4)
            exit(0);
        number[i] = atoi(line.c_str());
        i++;
    }
    // getline(iss,line,'.');
    // u_long ip = ((127 << 24) | (0 << 16) | (0 << 8) | 1)
    // std::cout << host << std::endl;
    this->host = ((number[0] << 24) | (number[1] << 16) | (number[2] << 8) | number[3]);
}

u_long Server::getHost() const
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