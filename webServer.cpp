/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:04:20 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/07 09:16:12 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"webServer.hpp"

webServer::webServer(const std::string& nameFile) : nameFile(nameFile)
{
    
}

webServer::webServer()
{
    
}

bool parsingLocation(const std::string& information)
{
    int cont = 0;
    size_t len = information.length();
    for (size_t i = 0; i < len; i++)
    {
        if (information[i] == ' ')
        {
            if (cont == 3 && (i + 1 < len && information[i + 1] == '-' && information[i + 2] == ' ' ))
                return true;
            cont++;        
        }
    }
    return false;
}

void webServer::loadLocation()
{
}

void webServer::loadConfigFile()
{
    Server server;
    Location location;
    bool status = true;
    int cont = 0;
    std::ifstream configFile;
    configFile.open(this->nameFile.c_str());
    std::string line;
    while (std::getline(configFile,line))
    {
        if(line == "server:")
        {
            cont = 0;
            while(std::getline(configFile,line))
            { 
                
                if (line.empty())
                { 
                    ++cont;
                   std::getline(configFile,line);
                   if (line == "  location:")
                   {
                        while (std::getline(configFile,line))
                        {
                            if (line.empty())
                            {
                                ++cont;
                                status = false;
                                break;
                            }
                            locations.push_back(line);
                        }
                        if (!status)
                            break;
                   }
                   else
                        std::cout << "test ===> " << std::endl;
                }
                lines.push_back(line); 
            }
            location.loadLocation(locations);
            // std::vector<std::string>::iterator it = locations.begin();
            // std::cout << "-------------\n";
            // while (it != locations.end())
            // {
            //    std::cout << *it << std::endl;
            //    ++it;
            // }
            // std::cout << "-------------\n";
            lines.clear();
            locations.clear();
        }
        else
            std::cout <<"test" << line << std::endl;
    }
    // if(!status || lines.empty() || locations.empty())
    //     throw std::runtime_error("error 1"); 
    // servers.push_back(server);
}

webServer::~webServer()
{
}