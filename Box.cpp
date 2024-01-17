/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:45 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/17 23:54:45 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Box.hpp"

Box::Box()
{
}

Box::Box(const Box& other)
{
    *this = other;
}

Box& Box::operator=(const Box& other)
{
   if (this != &other)
   {
        _InfoServer = other._InfoServer;
   }
   return *this;
}

void Box::setInfo(const webServer& InfoServer)
{
    _InfoServer = InfoServer;
}

void Box::readRequest(int fdRequest, int epollFd)
{
    char buffer[1024];
    int bytesRead = recv(fdRequest, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) 
    {
        std::cout << "Client disconnected." << std::endl;
        close(fdRequest);
        epoll_ctl(epollFd, EPOLL_CTL_DEL, fdRequest, 0);
    }
    buffer[bytesRead] = '\0';
    std::string buff(buffer);
}

void Box::setUpServer(webServer& data)
{
    std::vector<int>::iterator it;
    std::vector<int>::difference_type d;
    std::vector<int> fds;
    struct sockaddr_in host_add;
    struct sockaddr_in client_addr;
    epoll_event event;
    
    size_t numberOfServer = data.getServer().size();
    socklen_t client_addrlen = sizeof(client_addr);
    int epollFd = epoll_create(1);
    for (size_t i = 0; i < numberOfServer; i++)
    {
        int socket_server = socket(AF_INET,SOCK_STREAM,0);
        int reuseaddr = 1;
        setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
        if (socket_server < 0)
            throw std::runtime_error("Error\ncan not open this socket");
        std::cout << "Create Socket \n";
        host_add.sin_family = AF_INET;
        host_add.sin_port = htons(data.getServer().at(i).getListen());
        host_add.sin_addr.s_addr = htonl(data.getServer().at(i).getHost());
        if (bind(socket_server,reinterpret_cast<struct sockaddr*>(&host_add),sizeof(host_add)) < 0)
            throw std::runtime_error("Error\nbinding the socket");
        if (listen(socket_server,SOMAXCONN) == -1)
            throw std::runtime_error("Error\nlistening the socket");
        event.events = EPOLLIN;
        event.data.fd = socket_server;
        if (epoll_ctl(epollFd,EPOLL_CTL_ADD,socket_server,&event))
        {
            close(socket_server);
            close(epollFd);
            throw std::runtime_error("Error adding server socket to epoll");
        }
        fds.push_back(socket_server);
    }
    epoll_event events[10];
    std::map<int,Client> clients;
    while (true)
    {
        int client_socket;
        int numEvents = epoll_wait(epollFd, events, 10, -1);
        // signal(SI);
        for (int i = 0; i < numEvents; i++)
        {
            if ((it = std::find(fds.begin(),fds.end(),events[i].data.fd)) != fds.end())
            {
                d = it - fds.begin();
                client_socket = accept(events[i].data.fd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addrlen);
                if (client_socket < 0)
                    perror("accept");
                Client client;
                clients[client_socket] = client;
                data.getServer().at(d).setClient(clients);
                std::cout << "postion of server  " << d << std::endl;
                std::cout << "Client connected." << std::endl;
                event.events = EPOLLIN | EPOLLOUT ;
                event.data.fd = client_socket;
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, client_socket, &event) == -1) 
                {
                    std::cerr << "Error adding client socket to epoll." << std::endl;
                    close(client_socket);
                }
                // fdServer.push_back(std::pair<>)
                
            }
            else
            {
                ssize_t bytesRead = 0;
                if (events[i].events & EPOLLIN)
                {
                    readRequest(events[i].data.fd,epollFd);
                }
                else if ((events[i].events & EPOLLOUT))
                {
                    std::cout << "----------" << std::endl;
                    char resp[] = "HTTP/1.0 200 OK\r\n"
                    "Server: webserver-c\r\n"
                    "Content-type: text/html\r\n\r\n"
                    "<html><div class=\"main\"><h1>Welcome To GFG</h1><h3>Choose Your Gender</h3><form><label>Male<input type=\"radio\" 'name=\"gender\" value=\"male\" /></label><label>Female<input type=\"radio\"name=\"gender\" value=\"female\" /></label></form></div></html>\r\n";
                    int fd = write(events[i].data.fd,resp,strlen(resp));
                    std::cout << "EPOLLOUT " << bytesRead << " " << fd << std::endl;
                    std::cout << "test :"<< events[i].data.fd << std::endl;
                    if (fd <= 0)
                    {
                        perror("Error :");
                        exit(0);
                    }
                    close(events[i].data.fd);
                }
            }
            
        }
    }
}

Box::~Box()
{
}
