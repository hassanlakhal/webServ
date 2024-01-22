/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:41:04 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/22 21:47:38 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

// #include "webServer.hpp"
// #include"errorMessage.hpp"
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
        std::map<int,std::string > eroorPage;
        std::vector<Location> Locations;
        std::map<int, Client> clinets;
        long long client_max_body_size;
    public:
        Server();
        Server(const Server& other);
        void addLocation(Location* location);
        void setListen(std::string& listen);
        void setHost(std::string& host);
        void setMaxBodySize(std::string& maxBodySize);
        void setRoot(std::string& root);
        void setClient(std::map<int ,Client> & ClinetData);
        void setPathError(std::string& path);
        Server& operator=(const Server& other);
        __int16_t getListen() const;
        const std::vector<Location>& getLocation() const;
        std::string getRoot() const;
        u_long getHost() const;
        const std::map<int , std::string>& getErrorPath() const;
        Server* createServer();
        long long getMaxBodySize() const;
        std::string trim(std::string& word);
        virtual ~Server() throw();
};

#endif