/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/06 10:15:38 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
class Location
{
    private:
        std::vector<std::pair<std::string, std::string> > pairs;
        std::string path;
        std::string auto_index;
        std::vector<std::string> methods;
        std::vector<std::string> index;
        std::map<std::string, std::string> cgi_path;
        // long proxy_read_time_out;
    public:
        Location();
        ~Location();
};

#endif