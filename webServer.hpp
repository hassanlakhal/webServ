/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:05:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/06 10:27:39 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "Location.hpp"
#include <sstream>
#include <utility>

class Location;
class Server;
class webServer
{
    private:
        std::vector<Server> servers;
        std::string nameFile;
        std::vector<std::string> lines;
        std::vector<std::string> locations;
    protected:
        int listen;
        std::string host;
        std::string root;
        std::vector<Location> Locations;
    public:
        webServer();
        webServer(const std::string &nameFile);
        void loadConfigFile();
        void loadLocation();
        ~webServer();
};
#include "Server.hpp"
#endif