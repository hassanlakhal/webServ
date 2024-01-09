/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:05:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/08 21:49:22 by hlakhal-         ###   ########.fr       */
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
        std::vector<Server *> servers;
        std::string nameFile;
    public:
        webServer();
        webServer(const std::string &nameFile);
        void loadConfigFile();
        void loadLocation();
        void addServer(Server * s);
        ~webServer();
};

#endif