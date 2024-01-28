/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:45 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/28 23:07:09 by hlakhal-         ###   ########.fr       */
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

int Box::matchLocation(std::vector<Location>& loc, std::string path, int id)
{
    int i = 0;
    for (std::vector<Location>::iterator it = loc.begin(); it != loc.end(); ++it)
    {
        if (it->getPath() == path)
            return i;
        i++;
    }
    throw errorMessage(404,id);
}

void Box::methodAllowd(std::vector<std::string>& methods, const std::string& method, int id)
{
    std::vector<std::string> temV;
    temV.push_back("POST");
    temV.push_back("GET");
    temV.push_back("DELETE");
    std::vector<std::string>::iterator it1 = find(temV.begin(),temV.end(),method);
    if (it1 != temV.end())
    {
        std::vector<std::string>::iterator it = find(methods.begin(),methods.end(),method);
        if (it != methods.end())
            return ;
    }
    throw errorMessage(405,id);  
}

bool Box::checkDup(const std::vector<Server>& sr) 
{
    for (size_t i = 0; i < sr.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < sr.size(); ++j)
        {
            if ((sr[i].getHost() == sr[j].getHost()) && (sr[i].getListen() == sr[j].getListen()))
                return true;
        }
    }
    return false;
}


bool Box::checkName(const std::vector<Server>& sr, std::string name, size_t  &i) 
{
    (void)name;
    for (; i < sr.size(); ++i)
    {
        if(sr[i].getServerName() == name)
            return true;
    }
    return false;
}

void Box::sendRequest(int fd)
{
    int idOfServer = 0;
    size_t  i = 0;
    std::map<std::string, std::string> mapInfo = clients[fd].getInfoMap();
    if(checkDup(_InfoServer.getServer()))
    {
        // std::cout << mapInfo["Host"] << std::endl;
        if (checkName(_InfoServer.getServer(), mapInfo["Host"],i))
             idOfServer = i;
    }
    else
        idOfServer = clients[fd].getServerId();
    std::cout << "name server : " << _InfoServer.getServer()[idOfServer].getServerName() <<std::endl;
    std::vector<Location> loc = _InfoServer.getServer()[idOfServer].getLocation();
    int ind = matchLocation(loc,clients[fd].getPath(),idOfServer);    
    if (!(_InfoServer.getServer()[idOfServer].getLocation()[ind].getRediract().empty()))  
       throw errorMessage(301,idOfServer,ind);
    std::vector<std::string> methods = _InfoServer.getServer()[idOfServer]\
                                        .getLocation()[ind].getMethods();
    methodAllowd(methods,clients[fd].getMethod(),idOfServer);
    // std::cout <<"size of body " << clients[fd].getBody().size() << std::endl;
    // for (std::size_t i = 0; i < clients[fd].getBody().size(); ++i) 
    // {
    //     std::cout << (clients[fd].getBody()[i]) << "";
    // }
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
    if(!value.empty())
        return 301;
    return 200;
}

std::string Box::makeRepence(int fd, std::string value)
{
    std::string start_line ,header ,body ,result ,name_server, location;
    mapR errorMap = _InfoServer.getServer()[clients[fd].getServerId()].getErrorPath();
    int number = findKey(errorMap,value);
    if(number != 200)
    {
        if (number == 301)
            location = "Location: " + value + "\r\n";
        else
        {
            std::string line;
            std::ifstream file(value.c_str());
            while (std::getline(file,line))
                body.append(line);
        }
        std::stringstream ss;
        ss << number;
        result = ss.str();
    }
    else
        result = "200";
    name_server = "test";
    start_line = "HTTP/1.0 " + result + " error" + "\r\n";
    header = "Server: " + name_server + "\r\n" + "Content-type: text/html\r\n" + location + "\r\n";
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
        std::string buff(buffer,bytesRead);
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
    Repence rep;
    int epollFd = epoll_create(1);
      std::string res;
    _InfoServer = data;
    for (size_t i = 0; i < numberOfServer; i++)
    {
        int socket_server = socket(AF_INET,SOCK_STREAM,0);
        if (socket_server < 0)
            throw std::runtime_error("Error\ncan not open this socket");
        int reuseaddr = 1;
        if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuseaddr, sizeof(int)) < 0) 
        {
            throw std::runtime_error("Error\nsetting SO_REUSEADDR option");
        }
        std::cout << "Create Socket \n";
        host_add.sin_family = AF_INET;
        host_add.sin_port = htons(data.getServer().at(i).getListen());
        if (data.getServer().at(i).getHost())
            host_add.sin_addr.s_addr = htonl(data.getServer().at(i).getHost());
        else
            host_add.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(socket_server,reinterpret_cast<struct sockaddr*>(&host_add),sizeof(host_add)) < 0)
        {
            perror("error : ");
            throw std::runtime_error("Error\nbinding the socket");
        }   
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
        // signal(SIG_PIP);
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
                clients[events[i].data.fd].setRepence(rep);
                // std::cout << "postion of server  " << d << std::endl;
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
                bool status = clients[events[i].data.fd].getRepence().getStatusRepence();
                if (events[i].events & EPOLLIN && status)
                {
                    try
                    {
                        readRequest(events[i].data.fd, epollFd);
                    }
                    catch (const errorMessage& e)
                    {
                        rep.setValues(false,events[i].data.fd,e.getStatusCode(),e.what());
                        std::cout << "fd : "<< events[i].data.fd << std::endl;
                        // std::cout << e.what() << std::endl;
                        clients[events[i].data.fd].setRepence(rep);
                    }
                }
                else if ((events[i].events & EPOLLOUT) && !status)
                {
                    // std::cout << "fd : "<< events[i].data.fd << std::endl;
                    rep.sendRepence(events[i].data.fd);
                }

            }
            
        }
    }
}

Box::~Box()
{
}
