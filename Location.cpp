/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:32 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/07 09:18:44 by hlakhal-         ###   ########.fr       */
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

void Location::loadLocation(std::vector<std::string>& location)
{
    std::string key, value;
    std::vector<std::string>::iterator it = location.begin();
    std::cout << "============"<< "\n";
    for (; it != location.end(); it++)
    {
        std::string input(*it);
        std::cout << input << std::endl; 
    //     // if (!parsingLocation(input))
    //     //     throw std::runtime_error("Error");
    //     std::string configStr = input.substr(6,input.length());
    //     for (size_t i = 0; i < configStr.length(); i++)
    //     {
    //        if ((configStr[i] == ':' && (configStr[i + 1] != ' ' )) 
    //             || !isalpha(configStr[0]))
    //             throw std::runtime_error("Error");
    //     }
    //     *it = configStr;
    // }
    // it = locations.begin();
    // for (; it != locations.end(); it++)
    // {
    //     std::istringstream iss(*it);
    //     while (std::getline(iss,key,':') && std::getline(iss,value))
    //     {
    //         if (referenceConfig(key))
    //             locationPairs.push_back(std::make_pair(key,value));
    //         else
    //         {
    //             locationPairs.clear();
    //             throw std::runtime_error("Error");
    //         }
    //     }
     }
} 
