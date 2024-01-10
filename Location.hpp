/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/10 19:31:21 by hlakhal-         ###   ########.fr       */
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
#include <stdexcept>
// #include"Server.hpp"
class Location
{
    protected:
        std::vector<std::pair<std::string, std::string> > locationPairs;
        std::string path;
        std::string auto_index;
        std::string  root;
        std::vector<std::string> methods;
        std::vector<std::string> index;
        std::map<std::string, std::string> cgi_path;
        // long proxy_read_time_out;
    public:
        Location();
        const Location& getLocation() const;
        Location* createLocation();
        class ErrorLocation: public std::runtime_error
        {
            public:
                ErrorLocation(const std::string& message);
        };
        void setPath(std::string& path);
        void setAutoIndex(std::string& AutoIndex);
        void setMethods(std::string& Methods);
        void setIndex(std::string& index);
        void setCgi(std::string& CgiPath);
        void setRoot(std::string& root);
        void setUpload(std::string& upload);
        // void setLocation(const std::vector<std::pair<std::string, std::string> >& pairs);
        ~Location();
};

#endif