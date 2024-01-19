/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingFile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/19 11:48:05 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsingFile.hpp"
#include"Box.hpp"

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
            return word.substr(0,i);
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
        if(information[i] == '-' || isalpha(information[i]))
            break;
    }
    return cont;
}
static std::string trim(std::string word)
{
    size_t first = word.find_first_not_of(" ");
    if (first == std::string::npos)
        return word;
    size_t last = word.find_last_not_of(" ");
    return word.substr(first, last - first + 1);
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
        if(trim(getLine(information))!= "location")
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


void fillLocation( std::ifstream& configFile,std::string& line, Server* s)
{
    Location *loc = new Location;
    while (std::getline(configFile,line) &&  ((line = lastTrim(line)) != "server:"))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if(!parsingLocation(line))
        {
            delete loc;
            throw std::runtime_error("Error in Location");
        }
        std::string word = getWordLocation(line,6,false);
        std::istringstream valueOfLocation(word);
        std::getline(valueOfLocation,word,':');
        std::getline(valueOfLocation,word);
        if(trim(getWordLocation(line,6,true)) == "path")
            loc->setPath(word);
        else if(trim(getWordLocation(line,6,true)) == "root")
            loc->setRoot(word);
        else if(trim(getWordLocation(line,6,true)) == "cgi_path")
            loc->setCgi(word);
        else if(trim(getWordLocation(line,6,true)) == "methods")
            loc->setMethods(word);
        else if(trim(getWordLocation(line,6,true)) == "autoindex")
            loc->setAutoIndex(word);
        else if(trim(getWordLocation(line,6,true)) == "upload")
            loc->setUpload(word);
        else if(trim(getWordLocation(line,6,true)) == "index")
            loc->setIndex(word);
        if (trim(getLine(line)) == "location")
        {
            s->addLocation(loc);
            fillLocation(configFile,line,s);
            delete loc;
            return ;
        }
    }
    s->addLocation(loc);
    delete loc;
}

void fillServer(std::ifstream& configFile)
{
    Server s;
    std::string line;
    size_t hint;
    while (std::getline(configFile,line))
    {
        hint = 0;
        if (line.empty() || trim(line)[0] == '#')
            continue;
        int ind = numberOfCharacter(line, ' ',hint);
        if (ind == 2)
            line = trim(line);
        else
            throw std::runtime_error("Missing space");
        std::string word = getWordLocation(line,2,false);
        std::istringstream valueOfLocation(word);
        std::getline(valueOfLocation,word,':');
        std::getline(valueOfLocation,word);
        if (trim(getLine(line)) == "listen")
            s.setListen(word);
        else if (trim(getLine(line)) == "host")
            s.setHost(word);
        else if (trim(getLine(line)) == "root")
            s.setRoot(word);
        else if (trim(getLine(line)) == "client_max_body_size")
            s.setMaxBodySize(word);
        else if(trim(getLine(line)) == "location")
            fillLocation(configFile,line,&s);
        if (line == "server:")
        {
            GlobalConfig.addServer(&s);
            fillServer(configFile);
            // delete s; 
            return ;
        }
    }
    GlobalConfig.addServer(&s);
    // delete s;
}

void loadingData(std::string& nameFile)
{

    Box loading;
    std::ifstream configFile;
    configFile.open(nameFile.c_str());
    std::string line;
    while (std::getline(configFile,line))
    {
        line = lastTrim(line);
        if (line.empty() || line[0] == '#')
            continue;
        if(line == "server:")
            fillServer(configFile);
        else
            std::cout <<"test" << line << std::endl;
    }
    configFile.close();
    loading.setUpServer(GlobalConfig); 
    // std::vector<Server>:: const_iterator it =  GlobalConfig.getServer().begin();
    // int count = 0;
    // while (it != GlobalConfig.getServer().end())
    // {
    //     Server server = *it;
    //     std::cout << "server : " << count++ << std::endl ;
    //     std::vector<Location>::const_iterator it1 = server.getLocation().begin();
    //     std::cout << server.getListen() << std::endl;
    //     std::cout << server.getRoot() << std::endl;
    //     std::cout << server.getHost() << std::endl;
    //     count = 0;
    //     while (it1 != server.getLocation().end())
    //     {
    //         std::cout << "  location : " << count++ << std::endl ;
    //         Location loc = *it1;
    //         std::cout << loc.getPath() << std::endl;
    //         std::cout << loc.getAutoIndex() << std::endl;
    //         it1++;
    //     }
    //     it++;
    // }
}