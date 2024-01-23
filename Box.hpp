/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:54 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/23 17:41:57 by hlakhal-         ###   ########.fr       */
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
#include"errorMessage.hpp"
typedef  std::map<int , std::string> mapR;
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
        int matchLocation(std::vector<Location>& loc, std::string path, int fd);
        std::string makeRepence(int fd, std::string value);
        Box& operator=(const Box& other);
        ~Box();
};

