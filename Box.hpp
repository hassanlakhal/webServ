/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:54 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/26 09:50:56 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_HPP
#define BOX_HPP

#include"webServer.hpp"
#include"methods/methods.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <algorithm>
#include"errorMessage.hpp"
#include<stack>
# define GREEN "\033[92m"
# define RESET "\033[0m"
# define RED "\033[31m"
# define CYAN "\033[96m"

typedef  std::map<int , std::string> mapR;

class Box
{
    private:
        webServer _InfoServer;
        std::map<int,Client> clients;
        std::string QueryString;
        __uint16_t   _listen;
        u_long      _host;
        void parssingRequest(std::string& buffer);
        void readRequest(int fdRequest, int epollFd);
    public:
        Box();
        Box(const Box& other);
        void setInfo(const webServer& InfoServer);
        void setUpServer(webServer& data);
        void sendRequest(int fd);
        int matchLocation(std::vector<Location>& loc, std::string path, int fd);
        void methodAllowd(std::vector<std::string>& methods, const std::string& method, int id);
        Box& operator=(const Box& other);
        bool checkDup(const std::vector<Server>& sr, std::vector<int>& posServer);
        bool checkName(const std::vector<Server>& sr, std::string name, size_t  &i,std::vector<int>& posServer);
        void makeSocketNonBlocking(int sockfd);
        std::map<int,Client> &getClients() ;
        std::string removeSlach(std::string& str);
        const std::string& getQueryString() const;
        // std::string FullQueryString(std::string& path);
        webServer& getWebServer() ;
        void sendResponse(int fd);
        void timeOut(int fd, clock_t endTime);
        static bool ComparePath(const Location& loc1, const Location& loc2);
        std::string generetPage(int status, std::map<int, std::string> httpMessage);
        ~Box();
};

#endif
