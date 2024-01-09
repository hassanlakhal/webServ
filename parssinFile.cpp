/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssinFile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/09 01:26:52 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"webServer.hpp"

webServer GlobalConfig;

void lastTrim(const std::string& str)
{
    size_t last  = find_last_not_of(str," \t");
    if (first == std::string::npos)
        return ;
   str.substr(0,last + 1);
}

std::string getLine(const std::string& word)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] == ':')
            return word.substr(0,i + 1);
    }
    return word;
}

int numberOfCharacter(const std::string& information, char c, size_t& i)
{
    int cont = 0;
    size_t len = information.length();
    for (; i < len; i++)
    {
        if (information[i] == c)
            cont++;
        if(information[i] == '-')
            break;
    }
    return cont;
}

bool parsingLocation(const std::string& information)
{
    size_t hint = 0;
    int ind = numberOfCharacter(information, ' ',hint);
    if(ind == 4)
    {
       if(hint != 4 || information[hint + 1] != ' ')
            return false;
    }
    else
        return false;
    return true;
}

void fillLocation(std::string& configFile, Server *s)
{
    Location *loc = new Location;
    
    while (std::getline(configFile,line))
    {
        lastTrim(line);
        if(!parsingLocation(line))
            throw std::runtime_error("Error");
        
        if (lastTrim(getLine(line)) == "  location")
        {
            fillLocation(configFile,s);
            s->addLocation(loc);
            return ;
        }
    }
    GlobalConfig.addServer(s);
}

void fillServer(std::string& configFile)
{
    Server *s = new Server;
    while (std::getline(configFile,line))
    {
        lastTrim(line);
        if (line.empty() || line[0] == '#')
            continue;
        if (lastTrim(getLine(line)) == "  location")
            fillLocation(configFile,s);
        else if (lastTrim(getLine(line)) == "  listen")
            setListen(line);
        else if (lastTrim(getLine(line)) == "  host")
            setHost(line);
        else if (lastTrim(getLine(line)) == "  root")
            setRoot(line);
        else if (lastTrim(getLine(line)) == "  client_max_body_size")
            setMaxBodySize(line);
        if (line == "server:")
            fillServer(configFile); 
    }
    delete s;
}

void loadingData(std::string& nameFile)
{
    std::ifstream configFile;
    configFile.open(this->nameFile.c_str());
    std::string line;
    while (std::getline(configFile,line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if(line == "server:")
        {
            fillServer(configFile);
        }
        else
            std::cout <<"test" << line << std::endl;
        
    }
}