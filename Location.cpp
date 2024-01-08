/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/08 07:28:41 by hlakhal-         ###   ########.fr       */
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

Location* Location::createLocation()
{
    Location* newLocation = new Location;
    return newLocation;
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

void Location::loadLocation(std::vector<std::string>& location)
{
    std::string key, value;
    int numberOfLine = 0;
    std::vector<std::string>::iterator it = location.begin();
    for (; it != location.end(); it++)
    {
        numberOfLine++;
        std::string input(*it);
        if (!parsingLocation(input))
            throw std::runtime_error("Error1");
        std::string configStr = input.substr(6,input.length());
        if (input == "  location:")
        {
            lineOfLocation.push_back(numberOfLine);
            numberOfLine = 0;
            continue;
        }
        for (size_t i = 0; i < configStr.length(); i++)
        {
           if ((configStr[i] == ':' && (configStr[i + 1] != ' ' )) 
                || !isalpha(configStr[0]))
                throw std::runtime_error("Error");
        }
        *it = configStr;
    }
    it = location.begin();
    for (; it != location.end(); it++)
    {
        std::istringstream iss(*it);
        while (std::getline(iss,key,':') && std::getline(iss,value))
        {
            locationPairs.push_back(std::make_pair(key,value));
        }
    }
    makeLocation();
} 

std::vector<Location *>  Location::makeLocation()
{
    std::vector<Location *> locations;
    size_t cont = lineOfLocation.size();
    std::cout << "-----\n";
    for (size_t i = 0; i < cont; i++)
    {
        std::cout << "create :" << std::endl;
        locations.push_back(new Location);    
    }
    return locations;
}