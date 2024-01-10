/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingFile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/10 18:56:06 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsingFile.hpp"

webServer GlobalConfig;

std::string lastTrim(const std::string& str)
{
    size_t last  = str.find_last_not_of(" \t");
    if (last == std::string::npos)
        return str;
   return str.substr(0,last + 1);
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
    else if(ind == 2)
    {
        if(information != "  location:")
            return false;
    }
    else
        return false;
    return true;
}

std::string getWordLocation(std::string& word, int pos, bool type)
{
    word = lastTrim(word);
    if (type)
       return getLine(word.substr(pos,word.length() + 1));
    return word.substr(pos,word.length() + 1);
}


void fillLocation( std::ifstream& configFile, Server *s)
{
    Location *loc = new Location;
    std::string line;
    while (std::getline(configFile,line) &&  ((line = lastTrim(line)) != "server:"))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if(!parsingLocation(line))
            throw std::runtime_error("Error in Location");
        std::string word = getWordLocation(line,6,false);
        std::istringstream valueOfLocation(word);
        std::getline(valueOfLocation,word,':');
        std::getline(valueOfLocation,word);
        if(getWordLocation(line,6,true) == "path:")
            loc->setPath(word);
        else if(getWordLocation(line,6,true) == "root:")
            loc->setRoot(word);
        else if(getWordLocation(line,6,true) == "cgi_path:")
            loc->setCgi(word);
        else if(getWordLocation(line,6,true) == "methods:")
            loc->setMethods(word);
        else if(getWordLocation(line,6,true) == "autoindex:")
            loc->setAutoIndex(word);
        else if(getWordLocation(line,6,true) == "upload:")
            loc->setUpload(word);
        if (lastTrim(getLine(line)) == "  location:")
        {
            s->addLocation(*loc);
            fillLocation(configFile,s);
            return ;
        }
    }
    delete loc;
}

void fillServer(std::ifstream& configFile)
{
    Server *s = new Server;
    // std::ifstream configFile(file);
    std::string line;
    while (std::getline(configFile,line))
    {
        line = lastTrim(line);
        if (line.empty() || line[0] == '#')
            continue;
        std::string word = getWordLocation(line,2,false);
        std::istringstream valueOfLocation(word);
        std::getline(valueOfLocation,word,':');
        std::getline(valueOfLocation,word);
        if (lastTrim(getLine(line)) == "  location:")
            fillLocation(configFile,s);
        else if (lastTrim(getLine(line)) == "  listen:")
            s->setListen(word);
        else if (lastTrim(getLine(line)) == "  host:")
            s->setHost(word);
        else if (lastTrim(getLine(line)) == "  root:")
            s->setRoot(word);
        else if (lastTrim(getLine(line)) == "  client_max_body_size:")
            s->setMaxBodySize(word);
        if (line == "server:")
        {
            GlobalConfig.addServer(s);
            fillServer(configFile); 
            return ;
        }
    }
    GlobalConfig.addServer(s);
    delete s;
}

void loadingData(std::string& nameFile)
{
    std::ifstream configFile;
    configFile.open(nameFile);
    std::string line;
    while (std::getline(configFile,line))
    {
        line = lastTrim(line);
        if (line.empty() || line[0] == '#')
            continue;
        if(line == "server:")
        {
            // std::string input(configFile);
            fillServer(configFile);
        }
        else
            std::cout <<"test" << line << std::endl;
    }
    // std::vector<Server *>:: iterator it =  GlobalConfig.getServer().begin();
    // while (it != GlobalConfig.getServer().end())
    // {
    //     Server *server = *it;
        
    //     it++;
    // }
    
}