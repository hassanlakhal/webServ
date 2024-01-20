/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:41:04 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/20 18:16:34 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

// #include "webServer.hpp"
#include "Location.hpp"
#include"Client.hpp"
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
class Server
{
    protected:
        __int16_t   listen;
        u_long      host;
        std::string root;
        std::string pathEroor;
        std::vector<Location> Locations;
        std::map<int, Client> clinets;
        int client_max_body_size;
    public:
        Server();
        void addLocation(Location* location);
        void setListen(std::string& listen);
        void setHost(std::string& host);
        void setMaxBodySize(std::string& maxBodySize);
        void setRoot(std::string& root);
        void setClient(std::map<int ,Client> & ClinetData);
        void setPathError(std::string& path);
        __int16_t getListen() const;
        const std::vector<Location>& getLocation() const;
        std::string getRoot() const;
        u_long getHost() const;
        Server* createServer();
        ~Server();
};

#endif