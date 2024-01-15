/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:12 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/15 21:09:49 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"setupServer.hpp"

void setupServer(webServer& data)
{
    size_t numbeOfServer = data.getServer().size();
    std::vector<int> fds;
    struct sockaddr_in host_add;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    for (size_t i = 0; i < numbeOfServer; i++)
    {
        int socket_server = socket(AF_INET,SOCK_STREAM,0);
        if (socket_server < 0)
            throw std::runtime_error("Error\ncan not open this socket");
        std::cout << "Create Socket \n";
        host_add.sin_family = AF_INET;
        host_add.sin_port = htons(data.getServer().at(i).getListen());
        host_add.sin_addr.s_addr = htonl(data.getServer().at(i).getHost());
        if (bind(socket_server,reinterpret_cast<struct sockaddr*>(&host_add),sizeof(host_add)) < 0)
            throw std::runtime_error("Error\nbinding the sokect");
        if (listen(socket_server,SOMAXCONN))
            throw std::runtime_error("Error\nlistening the sokect");
        fds.push_back(socket_server);
    }
    int client_socket = accept(fds[1], (struct sockaddr *)&client_addr, &client_addrlen);
    if (client_socket < 0)
        perror("accept");
    close(fds[1]);
    // std::cout << data.getServer().size() << std::endl;
     std::cout << "test : ------>" << fds[0] << std::endl;
}