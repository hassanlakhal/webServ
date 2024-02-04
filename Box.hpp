/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:54 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/04 02:34:17 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_HPP
#define BOX_HPP

#include"webServer.hpp"
#include"methods/methods.hpp"
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
        std::string QueryString;
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
        void methodAllowd(std::vector<std::string>& methods, const std::string& method, int id);
        Box& operator=(const Box& other);
        bool checkDup(const std::vector<Server>& sr);
        bool checkName(const std::vector<Server>& sr, std::string name, size_t  &i);
        void makeSocketNonBlocking(int sockfd);
        std::map<int,Client> &getClients() ;
        std::string removeSlach(std::string& str);
        const std::string& getQueryString() const;
        std::string FullQueryString(std::string& path);
        webServer& getWebServer() ;
        void sendResponse(int fd);
        ~Box();
};

#endif
