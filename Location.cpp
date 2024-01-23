/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/22 22:54:27 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Location.hpp"

Location::ErrorLocation::ErrorLocation(const std::string& message) : std::runtime_error(message)
{
}

Location::Location()
{
    this->index.insert("index.html");
    this->index.insert("index.htm");
}

Location::~Location()
{
}
const Location& Location::getLocation() const
{
   return *this;
}

std::string trim(std::string& word)
{
    size_t first = word.find_first_not_of(" ");
    if (first == std::string::npos)
        return word;
    size_t last = word.find_last_not_of(" ");
    return word.substr(first, last - first + 1);
}

const std::map<std::string, std::string>& Location::getCgiPath() const
{
    return this->cgi_path;
}

void Location::setPath(std::string& path)
{
    if (path[0] != ' ')
        throw Location::ErrorLocation("Error of line path 2");
    path = trim(path);
    this->path = path;
}

std::string Location::getPath() const
{
    return path;
}

void Location::setRoot(std::string& root)
{
    if (root[0] != ' ')
        throw Location::ErrorLocation("Missing space in line of Location");
    root = trim(root);
    this->root = root;
}
void Location::setCgi(std::string& path)
{
    if (path[0] != ' ')
        throw Location::ErrorLocation("Missing space in line of Location");
    std::vector<std::string> paths;
    paths.push_back(path);
    std::vector<std::string>::iterator it = paths.begin();
    std::string key, value;
    while (it != paths.end())
    {
        std::istringstream iss(*it);
        getline(iss,key,',');
        getline(iss,value);
        cgi_path[trim(key)] = trim(value);
        it++;
    }
}

void Location::setAutoIndex(std::string& AutoIndex)
{
    if (AutoIndex[0] != ' ')
        throw Location::ErrorLocation("Missing space in line of Location");
    AutoIndex = trim(AutoIndex);
    this->auto_index = AutoIndex;
}

std::string Location::getAutoIndex() const
{
    return this->auto_index;
}

void Location::setMethods(std::string& Methods)
{
    if (Methods[0] != ' ')
        throw Location::ErrorLocation("Missing space in line of Location");
    Methods = trim(Methods);
    std::istringstream iss(Methods);
    std::string line;
    while (getline(iss,line,' '))
    {
        this->methods.push_back(Methods);
    }
}

void Location::setIndex(std::string& index)
{
    std::string line;
    if (index[0] != ' ')
        throw Location::ErrorLocation("Missing space in line of Location");
    index = trim(index);
    std::istringstream iss(index);
    while (getline(iss,line,' '))
    {
        this->index.insert(line);
    }
}

void Location::setUpload(std::string& upload)
{
    if (upload[0] != ' ')
        throw Location::ErrorLocation("Missing space in line of Location");
    upload = trim(upload);
    this->upload = upload;
}

Location* Location::createLocation()
{
    Location* newLocation = new Location;
    return newLocation;
}
