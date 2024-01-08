/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/08 06:19:07 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include"Server.hpp"
class Location
{
    protected:
        std::vector<std::pair<std::string, std::string> > locationPairs;
        std::string path;
        std::string auto_index;
        std::vector<std::string> methods;
        std::vector<std::string> index;
        std::map<std::string, std::string> cgi_path;
        std::vector<int> lineOfLocation;
        // long proxy_read_time_out;
    public:
        Location();
        void loadLocation(std::vector<std::string>& locations);
        const Location& getLocation() const;
        Location* createLocation();
        std::vector<Location *> makeLocation();
        // void setLocation(const std::vector<std::pair<std::string, std::string> >& pairs);
        ~Location();
};

#endif