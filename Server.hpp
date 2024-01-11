/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:41:04 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/11 02:12:00 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

// #include "webServer.hpp"
#include "Location.hpp"

class Server
{
    protected:
        long listen;
        std::string host;
        std::string root;
        std::vector<Location> Locations;
        int client_max_body_size;
    public:
        Server();
        void addLocation(Location* location);
        void setListen(std::string& listen);
        void setHost(std::string& host);
        void setMaxBodySize(std::string& maxBodySize);
        void setRoot(std::string& root);
        long getListen() const;
        const std::vector<Location>& getLocation() const;
        std::string getRoot() const;
        std::string getHost() const;
        Server* createServer();
        ~Server();
};

#endif