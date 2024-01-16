/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:12 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/16 21:21:42 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"setupServer.hpp"


bool check(int fd, std::vector<int> fds)
{
    for (size_t i = 0; i < fds.size(); i++)
    {
        if (fds.at(i) == fd)
            return false;
    }
    return true;
}

void setupServer(webServer& data)
{
    
    size_t numberOfServer = data.getServer().size();
    std::vector<int> fds;
    Client *client;
    struct sockaddr_in host_add;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    int epollFd = epoll_create(1);
    epoll_event event;
    for (size_t i = 0; i < numberOfServer; i++)
    {
        int socket_server = socket(AF_INET,SOCK_STREAM,0);
        // int reuseaddr = 1;
        // setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
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
        for (int i = 0; i < numEvents; i++)
        {
            if (std::find(fds.begin(),fds.end(),events[i].data.fd) != fds.end())
            {
                client_socket = accept(events[i].data.fd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addrlen);
                if (client_socket < 0)
                    perror("accept");
                std::cout << "Client connected." << std::endl;
                event.events = EPOLLIN | EPOLLOUT ;
                event.data.fd = client_socket;
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, client_socket, &event) == -1) 
                {
                    std::cerr << "Error adding client socket to epoll." << std::endl;
                    close(client_socket);
                }
                client = new Client;
                clients[client_socket] = *client;
            }
            else if(check(events[i].data.fd,fds))
            {

                // std::cout << "+++\n";
                // char buffer[1024];
                // ssize_t bytesRead = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                // std::cout << client_socket << std::endl;
                // if (bytesRead <= 0) 
                // {
                //     std::cout << "Client disconnected." << std::endl;
                //     close(events[i].data.fd);
                //     epoll_ctl(epollFd, EPOLL_CTL_DEL, events[i].data.fd, 0);
                // } 
                // else
                // {
                    ssize_t bytesRead = 0;
                    bool ind = false;
                    if (events[i].events & EPOLLIN)
                    {
                        // char buffer[1024];
                        // bytesRead = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                        // if (bytesRead <= 0) 
                        // {
                        //     std::cout << "Client disconnected." << std::endl;
                        //     close(events[i].data.fd);
                        //     epoll_ctl(epollFd, EPOLL_CTL_DEL, events[i].data.fd, 0);
                        // }
                        std::cout << "EPOLLIN " << bytesRead << std::endl;
                        ind = true;
                        close(events[i].data.fd);
                       
                    }
                    else if ((events[i].events & EPOLLOUT) && !ind)
                    {
                        char resp[] = "HTTP/1.0 200 OK\r\n"
                        "Server: webserver-c\r\n"
                        "Content-type: text/html\r\n\r\n"
                        "<html><div class=\"main\"><h1>Welcome To GFG</h1><h3>Choose Your Gender</h3><form><label>Male<input type=\"radio\" 'name=\"gender\" value=\"male\" /></label><label>Female<input type=\"radio\"name=\"gender\" value=\"female\" /></label></form></div></html>\r\n";
                        int fd = write(events[i].data.fd,resp,strlen(resp));
                        std::cout << "EPOLLOUT " << bytesRead << std::endl;
                        if (fd == -1)
                        {
                            exit(0);
                        }
                        // std::cout << "Received data from client: " << buffer << std::endl;
                        close(events[i].data.fd);
                    }
            }
            
        }
    //    exit(0); 
    }
    std::cout << "test : ------>" << fds[0] << std::endl;
}