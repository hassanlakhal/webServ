/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:45 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/22 20:45:54 by hlakhal-         ###   ########.fr       */
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

void Box::parssingRequest(std::string& buffer)
{
//    int i;
   std::istringstream iss(buffer);
   std::string line;
   while (getline(iss,line))
   {
        std::cout << line << std::endl;
   }
}

void Box::sendRequest(int fd)
{

    (void)fd;  
    // for (std::size_t i = 0; i < clients[fd].getBody().size(); ++i) 
    // {
    //     std::cout << (clients[fd].getBody()[i]) << "";
    // }
    std::cout <<"Method => " << clients[fd].getMethod() << std::endl;
    // std::cout << _InfoServer.getServer()[clients[fd].getServerId()].getRoot() <<std::endl;
    // std::cout << std::endl; 
}

int findKey(const mapR& myMap, const std::string& value) 
{
    mapR::const_iterator it;
    for (it = myMap.begin(); it != myMap.end(); ++it) 
    {
        if (it->second == value) 
            return it->first;
    }
    return 200;
}

std::string Box::makeRepence(std::string& cont, int fd, std::string value)
{
    std::string start_line ,header ,body ,result ,name_server;
    mapR errorMap = _InfoServer.getServer()[clients[fd].getServerId()].getErrorPath();
    int number = findKey(errorMap,value);
    if(number != 200)
    {
        std::stringstream ss;
        ss << number;
        result = ss.str();
    }
    else
        result = "200";
    name_server = "test";
    start_line = "HTTP/1.0 " + result + " error" + "\r\n";
    header = "Server: " + name_server + "\r\n" + "Content-type: text/html\r\n\r\n";
    body = cont + "\r\n";
    return (start_line + header + body);
}

void Box::readRequest(int fdRequest, int epollFd)
{
    char buffer[1024] = {0};
    int bytesRead = recv(fdRequest, buffer, 1023, 0);
    if (bytesRead <= 0) 
    {
        std::cout << "Client disconnected." << std::endl;
        close(fdRequest);
        epoll_ctl(epollFd, EPOLL_CTL_DEL, fdRequest, 0);
    }
    else
    {
        std::string buff(buffer,sizeof(buffer));
        clients[fdRequest].setRequset(buff);
        if (clients[fdRequest].getfullRequset().find("\r\n\r\n") != std::string::npos)
        {
            if (clients[fdRequest].getLoadingHeader())
                clients[fdRequest].ParsingRequest();
            else
            {
                std::istringstream iss(buff);
                clients[fdRequest].setBody(iss);
            }
            sendRequest(fdRequest);
        }
    }
}

void Box::setUpServer(webServer& data)
{
    std::vector<int>::iterator it;
    std::vector<int>::difference_type d;
    std::vector<int> fds;
    struct sockaddr_in host_add;
    struct sockaddr_in client_addr;
    epoll_event event;
    epoll_event events[10];
    size_t numberOfServer = data.getServer().size();
    socklen_t client_addrlen = sizeof(client_addr);
    int epollFd = epoll_create(1);
    _InfoServer = data;
    
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
        if (epoll_ctl(epollFd,EPOLL_CTL_ADD,socket_server,&event) == -1)
        {
            close(socket_server);
            close(epollFd);
            throw std::runtime_error("Error adding server socket to epoll");
        }
        fds.push_back(socket_server);
    }
    while (true)
    {
        int client_socket;
        int numEvents = epoll_wait(epollFd, events, 10, -1);
        // signal(SI);
        bool sing = true;
        for (int i = 0; i < numEvents; i++)
        {
            if ((it = std::find(fds.begin(),fds.end(),events[i].data.fd)) != fds.end())
            {
                d = it - fds.begin();
                client_socket = accept(events[i].data.fd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addrlen);
                if (client_socket < 0)
                    perror("accept");
                Client client(d);
                clients[client_socket] = client;
                std::cout << "postion of server  " << d << std::endl;
                std::cout <<  client_socket << " Client connected." << std::endl;
                event.events = EPOLLIN | EPOLLOUT;
                event.data.fd = client_socket;
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, client_socket, &event) == -1) 
                {
                    std::cerr << "Error adding client socket to epoll." << std::endl;
                    close(client_socket);
                }
            }
            else
            {
                if (events[i].events & EPOLLIN && sing)
                {
                    try
                    {
                        readRequest(events[i].data.fd,epollFd);
                    }
                    catch(const errorMessage& e)
                    {
                        std::string line;
                        std::ifstream file(e.what());
                        if (!file.is_open())
                            throw std::runtime_error("file not exit");
                        std::string resp;
                        while (std::getline(file,line))
                            resp.append(line);
                        std::string res = makeRepence(resp,events[i].data.fd,e.what());
                        int fd = write(events[i].data.fd,res.c_str(),strlen(res.c_str()));
                        if (fd <= 0)
                        {
                            perror("Error :");
                            exit(0);
                        }
                        close(events[i].data.fd);
                    }
                }
                else if ((events[i].events & EPOLLOUT) && !sing)
                {
                    // std::cout << "----------" << std::endl;
                    // char resp[] = "HTTP/1.0 200 OK\r\n"
                    // "Server: webserver-c\r\n"
                    // "Content-type: text/html\r\n\r\n"
                    // "<html><div class=\"main\"><h1>Welcome To GFG</h1><h3>Choose Your Gender</h3><form><label>Male<input type=\"radio\" 'name=\"gender\" value=\"male\" /></label><label>Female<input type=\"radio\"name=\"gender\" value=\"female\" /></label></form></div></html>\r\n";
                    // int fd = write(events[i].data.fd,resp,strlen(resp));
                    // std::cout << "EPOLLOUT " << bytesRead << " " << fd << std::endl;
                    // std::cout << "test :"<< events[i].data.fd << std::endl;
                    // if (fd <= 0)
                    // {
                    //     perror("Error :");
                    //     exit(0);
                    // }
                    // close(events[i].data.fd);
                }
            }
            
        }
    }
}

Box::~Box()
{
}
