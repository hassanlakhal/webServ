/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:05:17 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/17 22:22:23 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "Location.hpp"
#include "Server.hpp"
class webServer
{
    private:
        std::vector<Server> servers;
        std::string nameFile;
    public:
        webServer();
        webServer(const std::string &nameFile);
        webServer(const webServer& other);
        webServer& operator=(const webServer& other);
        void loadConfigFile();
        void loadLocation();
        void addServer(Server *s);
        Server* createServer();
        std::vector<Server> getServer() const;
        ~webServer();
};

#endif