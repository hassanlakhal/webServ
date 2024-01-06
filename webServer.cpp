/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:04:20 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/06 10:55:51 by hlakhal-         ###   ########.fr       */
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

bool referenceConfig(std::string value)
{
    std::map<std::string, int> configMap;
    configMap["path"] = 1;
    configMap["root"] = 2;
    configMap["upload"] = 3;
    configMap["autoindex"] = 4;
    configMap["methods"] = 5;
    configMap["index"] = 6;
    configMap["cgi_path"] = 7;
    configMap["proxy_read_time_out"] = 8;
    std::map<std::string, int>::iterator it = configMap.find(value);
    if (it != configMap.end())
        return true;
    return false;
}

void webServer::loadLocation()
{
    // Location config;
    std::vector<std::pair<std::string, std::string> > locationPairs;
    std::string key, value;
    std::vector<std::string>::iterator it = locations.begin();
    for (; it != locations.end(); it++)
    {
        std::string input(*it);
        if (!parsingLocation(input))
            throw std::runtime_error("Error");
        std::string configStr = input.substr(6,input.length());
        std::cout << configStr << std::endl;
        for (size_t i = 0; i < configStr.length(); i++)
        {
           if ((configStr[i] == ':' && (configStr[i + 1] != ' ' )) || !isalpha(configStr[0]))
                throw std::runtime_error("Error");
        }
        *it = configStr;
    }
    it = locations.begin();
    for (; it != locations.end(); it++)
    {
        std::istringstream iss(*it);
        while (std::getline(iss,key,':') && std::getline(iss,value))
        {
            if (referenceConfig(key))
                locationPairs.push_back(std::make_pair(key,value));
            else
            {
                locationPairs.clear();
                throw std::runtime_error("Error");
            }
        }
    }
    
    // return config;
}

void webServer::loadConfigFile()
{
    bool status = true;
    int cont = 0;
    std::ifstream configFile;
    configFile.open(this->nameFile);
    std::string line;
    while (std::getline(configFile,line))
    {
        if(line == "server:")
        {
            while(std::getline(configFile,line))
            {
                ++cont;
                if(line.length() && cont > 4)
                    throw std::runtime_error("error");
                else if(!line.length())
                {
                    cont = 0;
                    break;
                }
                lines.push_back(line);
            }
        }
        else if(line == "  location:")
        {
            while(std::getline(configFile,line))
            {
                if(!line.length())
                    break ;
                locations.push_back(line);
            }
        }
        else
            status = false;
    }
    if(!status || lines.empty() || locations.empty())
        throw std::runtime_error("error 1"); 
}

webServer::~webServer()
{
}