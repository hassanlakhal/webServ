/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingFile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:27:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/16 07:46:55 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsingFile.hpp"
#include"Box.hpp"
webServer GlobalConfig;

webServer& getMyServer()
{
    return GlobalConfig;
}
std::string lastTrim(const std::string& str)
{
    size_t last  = str.find_last_not_of(" \t");
    if (last == std::string::npos)
        return str;
   return str.substr(0,last + 1);
}
static std::string trim(std::string word)
{
    size_t first = word.find_first_not_of(" ");
    if (first == std::string::npos)
        return word;
    size_t last = word.find_last_not_of(" ");
    return word.substr(first, last - first + 1);
}

std::string getLine(const std::string& word)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] == ':')
            return word.substr(0,i);
    }
    throw Location::ErrorLocation("Error: Colon ':' not found in the string."); 
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

bool parsingLocation(const std::string& information)
{
    size_t hint = 0;
    int ind = numberOfCharacter(lastTrim(information), ' ',hint);
    if(ind == 4)
    {
       if(hint != 4 || information[hint + 1] != ' ')
            return false;
    }
    else if(ind == 2)
    {
        if(trim(getLine(information))!= "location")
              throw std::runtime_error("Error: Expected 'location' but found '" + trim(getLine(information)) + "'.");
    }
    else if (ind == 0)
    {
       if(trim(getLine(information)) != "server")
            throw std::runtime_error("Error: Expected 'server' block, but found '" + trim(getLine(information)) + "'.");
    }
    return true;
}

std::string getWordLocation(std::string& word, int pos, bool type)
{
    word = lastTrim(word);
    if (type)
       return getLine(word.substr(pos,word.length() + 1));
    return word.substr(pos,word.length() + 1);
}

void checkDupLine(const std::vector<std::string>& dupLine, std::string from)
{
    for (size_t i = 0; i < dupLine.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < dupLine.size(); ++j)
        { 
            if (dupLine[i] == dupLine[j])
                throw Location::ErrorLocation("Error: Duplicate line found: '"\
                + dupLine[i] + "'");
        }
    }
    if (from == "server")
    {
        bool hasListen = false;
        bool hasHost = false;
        for (size_t i = 0; i < dupLine.size(); ++i)
        {
            if (dupLine[i] == "listen")
                hasListen = true;
            else if (dupLine[i] == "host")
                hasHost = true;
        }
        if (!(hasListen && hasHost))
            throw Location::ErrorLocation("Error: For a server, it is necessary to have elements 'listen', and 'host'.");
    }
}

void fillLocation( std::ifstream& configFile,std::string& line, Server* s)
{
    Location loc(s->getRoot());
    std::vector<std::string> dupLine;
    while (std::getline(configFile,line) &&  ((line = lastTrim(line)) != "server:"))
    {
        if (line.empty() || trim(line)[0] == '#')
            continue;
        if(!parsingLocation(line))
            throw Location::ErrorLocation("Error: Missing space in this line.");
        std::string word = getWordLocation(line,6,false);
        std::istringstream valueOfLocation(word);
        std::getline(valueOfLocation,word,':');
        std::getline(valueOfLocation,word);
        if (trim(getWordLocation(line,6,true)) != "cgi_path")
            dupLine.push_back(trim(getWordLocation(line,6,true)));
        if(trim(getWordLocation(line,6,true)) == "path")
            loc.setPath(word);
        else if(trim(getWordLocation(line,6,true)) == "root")
            loc.setRoot(word);
        else if(trim(getWordLocation(line,6,true)) == "cgi_path")
            loc.setCgi(word);
        else if(trim(getWordLocation(line,6,true)) == "methods")
            loc.setMethods(word);
        else if(trim(getWordLocation(line,6,true)) == "autoindex")
            loc.setAutoIndex(word);
        else if(trim(getWordLocation(line,6,true)) == "upload")
            loc.setUpload(word);
        else if(trim(getWordLocation(line,6,true)) == "index")
            loc.setIndex(word);
        else if(trim(getWordLocation(line,6,true)) == "return")
            loc.setRedirect(word);
        else if(trim(getWordLocation(line,6,true)) == "listing_dir")
            loc.setListingDir(word);
        else if(trim(getWordLocation(line,6,true)) == "upload_path")
            loc.setUploadPath(word);
        else if (trim(getLine(line)) == "location")
        {
            checkDupLine(dupLine, "location");
            dupLine.clear();
            s->addLocation(&loc);
            fillLocation(configFile,line,s);
            return ;
        }
        else
        {
            throw Location::ErrorLocation("Error: '" + \
            trim(getWordLocation(line, 6, true)) +\
             "' is not allowed in the configuration or exist more space");
        }
           
    }
    checkDupLine(dupLine,"location");
    dupLine.clear();
    s->addLocation(&loc);
}

void confiServer(const std::string& word)
{
    std::vector<std::string> configs;
    configs.push_back("listen");
    configs.push_back("host");
    configs.push_back("root");
    configs.push_back("client_max_body_size");
    configs.push_back("error_page");
    configs.push_back("server_name");
    configs.push_back("location");
    std::vector<std::string>::iterator it =  std::find(configs.begin(), configs.end(), word);
    if(it == configs.end())
        throw std::runtime_error("Error: Configuration parameter not recognized.");
}

void fillServer(std::ifstream& configFile)
{
    Server s;
    std::string line;
    size_t hint;
    std::vector<std::string> dupLine;
    while (std::getline(configFile,line))
    {
        hint = 0;
        if (line.empty() || trim(line)[0] == '#')
            continue;
        int ind = numberOfCharacter(line, ' ',hint);
        if (trim(line) != "server:")
        {
            if (ind == 2)
                line = trim(line);
            else
                throw std::runtime_error("Error: Syntax error in the configuration.");
        }
        std::string word = getWordLocation(line,2,false);
        std::istringstream valueOfLocation(word);
        std::getline(valueOfLocation,word,':');
        std::getline(valueOfLocation,word);
        if (line != "server:")
        {
            confiServer(trim(getLine(line)));
            dupLine.push_back(trim(getLine(line)));
        }
        if (trim(getLine(line)) == "listen")
            s.setListen(word);
        else if (trim(getLine(line)) == "host")
            s.setHost(word);
        else if (trim(getLine(line)) == "root")
            s.setRoot(word);
        else if (trim(getLine(line)) == "client_max_body_size")
            s.setMaxBodySize(word);
        else if (trim(getLine(line)) == "error_page")
            s.setPathError(word);
        else if (trim(getLine(line)) == "server_name")
            s.setServerName(word);
        else if(trim(getLine(line)) == "location")
            fillLocation(configFile,line,&s);
        if (line == "server:")
        {
            checkDupLine(dupLine,"server");
            dupLine.clear();
            GlobalConfig.addServer(&s);
            fillServer(configFile);
            return ;
        }
    }
    checkDupLine(dupLine,"server");
    dupLine.clear();
    GlobalConfig.addServer(&s);
}

void loadingData(std::string& nameFile)
{

    Box loading;
    std::ifstream configFile;
    configFile.open(nameFile.c_str());
    std::string line;
    int i = 0;
    while (std::getline(configFile,line))
    {
        if (line.empty() || trim(line)[0] == '#')
            continue;
        line = lastTrim(line);
        if(line == "server:")
            fillServer(configFile);
        else
           throw std::runtime_error("Error: Expected 'server:' block, but found '" + line + "'.");
        i++;
    }
    if(!i)
        throw std::runtime_error("empty file");
    configFile.close();
    loading.setUpServer(GlobalConfig);
}
