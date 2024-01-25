/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/25 17:31:25 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"


Server::Server()
{
    eroorPage[400] = "error_page/400.html";
    eroorPage[404] = "error_page/404.html";
    eroorPage[414] = "error_page/414.html";
    eroorPage[413] = "error_page/413.html";
    eroorPage[405] = "error_page/405.html";
    client_max_body_size = 2147483648;
    this->host = 0;
    // eroorPage[404] = "error_page/404.html";
    
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
    // std::cout << "***>"<< Locations.at(0).getRoot() << std::endl;
    // std::cout << location << std::endl;
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
    listen = trim(listen);
    std::istringstream iss(listen);
    if (listen.empty() || listen.find_first_not_of("0123456789") != std::string::npos)
        throw std::runtime_error("Error: Missing 'listen' value. Please provide a" \
                        "valid value for 'listen'.");
    long nb;
    iss >> nb;
    if (nb > std::numeric_limits<__uint16_t>::max())
        throw std::runtime_error("Error : out of range of 'listen' value.");
    this->listen = nb;
}

__uint16_t Server::getListen() const
{
    return this->listen;
}

void Server::setHost(std::string& host)
{
    std::string segment;
    u_long number[4];
    int count = 0;
    host = trim(host);
    std::istringstream iss(host);
    while (std::getline(iss, segment, '.') && count < 4) 
    {
        if (segment.empty() || segment.find_first_not_of("0123456789") != std::string::npos 
                            || segment.length() >= 4)
            throw std::runtime_error("The IP address is not valid.");
        number[count] = atoi(segment.c_str());
        if (number[count] > static_cast<u_long>(255)) 
            throw std::runtime_error("The IP address is not valid.");
        count++;
    }
    if (count != 4)
        throw std::runtime_error("Error");
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
    root = trim(root);
    this->root =  root;
}

const std::string& Server::getRoot() const
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
        if (nb >= 400 && nb < 599)
        {
            std::ifstream file(value.c_str());
            if (file.is_open())
                eroorPage[nb] = value;
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
    if (maxBodySize[0] != ' ')
        throw std::runtime_error("error line client_max_body_size");
    std::string size;
    if (maxBodySize[maxBodySize.length() - 1] == 'K') 
    {
        size = maxBodySize.substr(0, maxBodySize.length() - 1);
        std::istringstream iss(size);
        long long nb;
        iss >> nb;
        this->client_max_body_size = nb * 1024;
    }
    else if (maxBodySize[maxBodySize.length() - 1] == 'M') 
    {
        size = maxBodySize.substr(0, maxBodySize.length() - 1);
        std::istringstream iss(size);
        long long nb;
        iss >> nb;
        this->client_max_body_size = nb * 1024 * 1024;
    } 
    else if (maxBodySize[maxBodySize.length() - 1] == 'G') 
    {
        size = maxBodySize.substr(0, maxBodySize.length() - 1);
        std::istringstream iss(size);
        long long nb;
        iss >> nb;
        this->client_max_body_size = nb * 1024 * 1024 * 1024;
    }
    else
        std::runtime_error("error line client_max_body_size");
}

long long Server::getMaxBodySize() const
{
    return this->client_max_body_size;
}