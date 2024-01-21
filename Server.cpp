/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/21 22:25:17 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"


Server::Server()
{
    eroorPage[400] = "error_page/400.html";
    eroorPage[404] = "error_page/404.html";
    
}

Server::~Server() throw()
{
}

Server::Server(const Server& other)
{
    listen = other.listen;
    host = other.host ;
    root = other.root;
    eroorPage = other.eroorPage;
    Locations = other.Locations;
    clinets = other.clinets;
    client_max_body_size = other.client_max_body_size;
}

Server& Server::operator=(const Server& other)
{
    if (this == &other)
    {
        listen = other.listen;
        host = other.host ;
        root = other.root;
        eroorPage = other.eroorPage;
        Locations = other.Locations;
        clinets = other.clinets;
        client_max_body_size = other.client_max_body_size;
    }
    return *this;
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
    this->host = ((number[0] << 24) | (number[1] << 16) | (number[2] << 8) | number[3]);
}

std::string Server::trim(std::string& word)
{
    size_t first = word.find_first_not_of(" ");
    if (first == std::string::npos)
        return word;
    size_t last = word.find_last_not_of(" ");
    return word.substr(first, last - first + 1);
}

void Server::setClient(std::map<int , Client>& ClinetData)
{
    this->clinets = ClinetData;
}

u_long Server::getHost() const
{
    return host;
}
void Server::setRoot(std::string& root)
{
    if (root[0] != ' ')
        throw std::runtime_error("error line root");
    this->root =  root;
}

std::string Server::getRoot() const
{
    return root;
}

const std::map<int , std::string>& Server::getErrorPath() const
{
    return this->eroorPage;
}

const std::vector<Location>& Server::getLocation() const
{
    return this->Locations;
}

void Server::setPathError(std::string& path)
{
    if (path[0] != ' ')
        throw std::runtime_error("error line path");
    path = trim(path);
    std::string key , value;
    long nb;
    std::vector<std::string> paths;
    paths.push_back(path);
    std::vector<std::string>::iterator it = paths.begin();
    while (it != paths.end())
    {
        std::istringstream iss(*it);
        getline(iss,key,' ');
        getline(iss,value);
        std::istringstream number(key);
        number >> nb;
        if (nb >= 100 && nb < 599)
        {
            this->eroorPage[nb] = value;
            std::cout << nb << " ------------ "  << value<< std::endl;
        }
        else
        {
            std::cout << nb << " ------------ "  << value<< std::endl;
            throw std::runtime_error("out of range");
        }
        it++;
    }
    
}

void Server::setMaxBodySize(std::string& maxBodySize)
{
    (void)maxBodySize;
    // this->client_max_body_size = maxBodySize;
}