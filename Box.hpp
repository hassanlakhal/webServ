/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:54 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/20 15:52:50 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"webServer.hpp"
#include <iostream> 
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <algorithm>
class Box
{
    private:
        webServer _InfoServer;
        std::map<int,Client> clients;
        void parssingRequest(std::string& buffer);
        void readRequest(int fdRequest, int epollFd);
    public:
        Box();
        Box(const Box& other);
        void setInfo(const webServer& InfoServer);
        void setUpServer(webServer& data);
        void sendRequest(int fd);
        Box& operator=(const Box& other);
        ~Box();
};

