/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/11 16:39:00 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Location.hpp"

Location::ErrorLocation::ErrorLocation(const std::string& message) : std::runtime_error(message)
{
}

Location::Location()
{
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
        throw Location::ErrorLocation("Error of line path 3");
    root = trim(root);
    this->root = root;
    // std::cout << root << std::endl;
}
void Location::setCgi(std::string& path)
{
    if (path[0] != ' ')
        throw Location::ErrorLocation("Error of line path 1");
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
    this->auto_index = AutoIndex;
    // std::cout << AutoIndex << std::endl;
    (void)AutoIndex;
}

std::string Location::getAutoIndex() const
{
    return this->auto_index;
}

void Location::setMethods(std::string& Methods)
{
     if (Methods[0] != ' ')
        throw Location::ErrorLocation("Error of line path 1");
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
    std::cout << index << std::endl;
    (void)index;
}

void Location::setUpload(std::string& upload)
{
    (void)upload;
}

Location* Location::createLocation()
{
    Location* newLocation = new Location;
    return newLocation;
}
