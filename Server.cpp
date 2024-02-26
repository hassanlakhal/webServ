/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/26 14:39:37 by eej-jama         ###   ########.fr       */
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
    eroorPage[408] = "error_page/408.html";
    eroorPage[403] = "error_page/403.html";
    eroorPage[500] = "error_page/500.html";
    eroorPage[501] = "error_page/501.html";
    eroorPage[504] = "error_page/504.html";
    client_max_body_size = 2147483648;
    this->host = 0;
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
    name = other.name;
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
        name = other.name;
    }
    return *this;
}

void Server::addLocation(Location *location)
{
    if (root.empty() && location->getRoot().empty())
        throw std::runtime_error("Error: Root configuration missing. Please specify the root directory for the server or location.");
    Locations.push_back(*location);
    if (Locations.size() > 1)
    {
        for (size_t i = 0; i < Locations.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < Locations.size(); ++j)
            {
                if (Locations[i].getPath() == Locations[j].getPath())
                   throw std::runtime_error("Error: Duplicate location found. Path '" + Locations[i].getPath() + "' already exists.");
            }
        }
    }
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

void Server::setServerName(std::string& serverName)
{
    if (serverName[0] != ' ')
        throw std::runtime_error("error line serverName");
    serverName = trim(serverName);
    std::istringstream iss(serverName);
    std::string line;
    while (getline(iss,line,' '))
    {
        this->name.push_back(line);
    }
}

void Server::setHost(std::string& host)
{
    std::string segment;
    u_long number[4];
    int count = 0;
    host = trim(host);
    std::istringstream iss(host);
    if (host != "localhost")
    {
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
}

const std::vector<std::string>& Server::getServerName() const
{
    return this->name;
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
    if(root.empty() || root.length() < 2){
        throw std::runtime_error("error line root");
    }
    if(root[0] != '.' || root[1] != '/')
        throw std::runtime_error("error line root");
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
            throw std::runtime_error("out of range");
        it++;
    }
}

bool isNumber(const std::string& s)
{
    if (s.empty())
        throw std::runtime_error("Error: Invalid format for 'client_max_body_size'. It should be a number followed by 'K', 'M', or 'G'.");
    int j = 0;
    for (size_t i = 0; i < s.length(); ++i)
    {
        if (s[i] == '.' && j < 1)
        {
            j++;
            continue ;
        }
        if (!isdigit(s[i]))
             throw std::runtime_error("Error: Invalid format for 'client_max_body_size'. It should be a number followed by 'K', 'M', or 'G'.");
    }
    return true;
}

void Server::setMaxBodySize(std::string& maxBodySize)
{
    if (maxBodySize.empty() || maxBodySize[0] != ' ')
        throw std::runtime_error("Error: Invalid format for 'client_max_body_size'. It should start with a space.");

    maxBodySize = trim(maxBodySize);

    char unit = maxBodySize[maxBodySize.length() - 1];
    std::string size = maxBodySize.substr(0, maxBodySize.length() - 1);
    isNumber(size);
    std::istringstream iss(size);
    double nb;
    iss >> nb;
    switch (unit)
    {
        case 'B':
            this->client_max_body_size = nb;
            break;
        case 'K':
            this->client_max_body_size = nb * 1024;
            break;
        case 'M':
            this->client_max_body_size = nb * 1024 * 1024;
            break;
        case 'G':
            this->client_max_body_size = nb * 1024 * 1024 * 1024;
            break;
        default:
            throw std::runtime_error("Error: Invalid format for 'client_max_body_size'. It should end with 'B', 'K', 'M', or 'G'.");
    }
}

double Server::getMaxBodySize() const
{
    return this->client_max_body_size;
}
