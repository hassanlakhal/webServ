/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/09 23:47:36 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Location.hpp"

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

void Location::setPath(std::string& path)
{
    (void)path;
    // std::cout << path << std::endl;
}

void Location::setRoot(std::string& root)
{
    (void)root;
    // std::cout << root << std::endl;
}
void Location::setCgi(std::string& path)
{
    std::vector<std::string> paths;
    std::cout << "==>" << path << std::endl;
    paths.push_back(path);
}

void Location::setAutoIndex(std::string& AutoIndex)
{
    (void)AutoIndex;
}

void Location::setMethods(std::string& Methods)
{
    (void)Methods;
}

void Location::setIndex(std::string& index)
{
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
