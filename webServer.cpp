/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:04:20 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/10 22:52:22 by hlakhal-         ###   ########.fr       */
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

const std::vector<Server>& webServer::getServer() const
{
    return this->servers;
}

void webServer::loadConfigFile()
{
    // // Server server;
    // // Location location;
    // bool status = true;
    // std::ifstream configFile;
    // configFile.open(this->nameFile.c_str());
    // std::string line;
    // while (std::getline(configFile,line))
    // {
    //     if(line == "server:")
    //     {
    //         while(std::getline(configFile,line))
    //         { 
                
    //             if (line.empty())
    //             { 
    //                std::getline(configFile,line);
    //                if (line == "  location:")
    //                {
    //                     while (std::getline(configFile,line))
    //                     {
    //                         if (line.empty())
    //                         {
    //                             status = false;
    //                             break;
    //                         }
    //                         locations.push_back(line);
    //                     }
    //                     if (!status)
    //                         break;
    //                }
    //                else
    //                     std::cout << "test ===> " << std::endl;
    //             }
    //             lines.push_back(line); 
    //         }
    //         location.loadLocation(locations);
    //         // location = location.getLocation();
    //         // std::vector<std::string>::iterator it = locations.begin();
    //         // std::cout << "-------------\n";
    //         // while (it != locations.end())
    //         // {
    //         //    std::cout << *it << std::endl;
    //         //    ++it;
    //         // }
    //         // std::cout << "-------------\n";
    //         lines.clear();
    //         locations.clear();
    //     }
    //     else
    //         std::cout <<"test" << line << std::endl;
        
    // }
}

webServer::~webServer()
{
}