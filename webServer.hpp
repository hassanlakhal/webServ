/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:05:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/07 02:36:25 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "Location.hpp"
class Location;
class Server;
class webServer
{
    private:
        std::vector<Server> servers;
        std::string nameFile;
        std::vector<std::string> lines;
        std::vector<std::string> locations;
    public:
        webServer();
        webServer(const std::string &nameFile);
        void loadConfigFile();
        void loadLocation();
        ~webServer();
};

#endif