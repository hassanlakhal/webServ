/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/07 22:59:13 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"


Server::Server()
{
}

Server::~Server()
{
}

void Server::addLocation(Location& location)
{
    Locations.push_back(location);
}

Server* Server::createServer()
{
    Server *newServer = new Server;
    return newServer;
}