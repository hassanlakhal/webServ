/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:45 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/12 19:18:57 by hlakhal-         ###   ########.fr       */
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

std::string  Box::removeSlach(std::string& str)
{
	size_t pos = str.find_first_not_of('/');
	str.erase(0, pos);
	pos = str.find_last_not_of('/');
	if (pos != std::string::npos)
		str.erase(pos + 1);
	std::vector<std::string> result;
	std::size_t start = 0;
	std::size_t end = str.find('/');
	while (end != std::string::npos)
	{
		std::string temp = str.substr(start, end - start);
		if (!temp.empty())
			result.push_back("/" + temp);
		start = end + 1;
		end = str.find('/', start);
	}
	result.push_back("/" + str.substr(start));
	std::string path;
	std::vector<std::string>::iterator it = result.begin();
	for (; it != result.end(); it++)
	{
		path.append(*it);
	}
	return path;
}

bool Box::ComparePath(const Location& loc1, const Location& loc2)
{
	return loc1.getPath().length() < loc2.getPath().length();
}

int Box::matchLocation(std::vector<Location>& loc, std::string path, int id)
{
	std::vector<std::pair<std::string, int> > hashTable;
	for (size_t i = 0; i < loc.size(); ++i)
	{
		hashTable.push_back(std::make_pair(loc[i].getPath(), i));
	}
	path = removeSlach(path);
	path = FullQueryString(path);
	// int hashValue = hash(path);
	for (size_t i = 0; i < hashTable.size(); ++i)
	{
		// exit(0);
		if (hashTable[i].first == path)
		{
			return hashTable[i].second;
		}
	}
	// std::cout << "Path : " << path <<std::endl;
	path = path.substr(0, path.find_last_of('/'));
	if (!path.empty())
		return matchLocation(loc,path,id);
	else
	{
		for (size_t i = 0; i < hashTable.size(); ++i)
		{
			if (hashTable[i].first == "/")
			{
				return hashTable[i].second;
			}
		}
	}
	return -1;
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

bool Box::checkDup(const std::vector<Server>& sr, std::vector<int>& posServer)
{
	for (size_t i = 0; i < sr.size(); ++i)
	{
		if ((sr[i].getHost() == _host) && (sr[i].getListen() == _listen))
		{
			posServer.push_back(i);
		}
	}
	if (posServer.size() > 1)
		return true;
	return false;
}


bool Box::checkName(const std::vector<Server>& sr, std::string name, size_t  &i,std::vector<int>& posServer)
{
	(void)name;
	for (; i < posServer.size(); ++i)
	{
		std::vector<std::string> names = sr[i].getServerName();
		std::vector<std::string>::iterator it = find(names.begin(),names.end(),name);
		if(it != names.end())
			return true;
	}
	return false;
}

void Box::sendRequest(int fd)
{
	int idOfServer = 0;
	std::string pathLocation;
	std::vector<int> posServer;
	std::map<std::string, std::string> mapInfo = clients[fd].getInfoMap();
	if(checkDup(_InfoServer.getServer(),posServer))
	{
		size_t  i = posServer.at(0);
		std::istringstream iss(mapInfo["Host"]);
		std::string host;
		getline(iss,host,':');
		// std::cout << mapInfo["Host"] << std::endl;
		if (checkName(_InfoServer.getServer(), host,i,posServer))
			 idOfServer = i;
	}
	else
		idOfServer = clients[fd].getServerId();
	clients[fd].setServerId(idOfServer);
	// std::cout << "name server : " << _InfoServer.getServer()[idOfServer].getServerName().at(0)\
	// << " " << clients[fd].getServerId() <<std::endl;
	std::vector<Location> loc = _InfoServer.getServer()[idOfServer].getLocation();
	if(!clients[fd].getMatchedTime()){
		int ind = matchLocation(loc,clients[fd].getPath(),idOfServer);
		if (ind == -1)
			throw errorMessage(404,idOfServer);
		clients[fd].setPathLoc(clients[fd].getPath());
		pathLocation = loc[ind].getRoot() + "/" + clients[fd].getPath().substr(loc[ind].getPath().length());
		clients[fd].setPath(pathLocation);
		clients[fd].setInd(ind);
		clients[fd].setMatchedTime(true);
	}
	int ind = clients[fd].getInd();
	if (!(_InfoServer.getServer()[idOfServer].getLocation()[ind].getRedirect().empty()))
	   throw errorMessage(301,idOfServer,ind);
	std::vector<std::string> methods = _InfoServer.getServer()[idOfServer]\
										.getLocation()[ind].getMethods();
	methodAllowd(methods,clients[fd].getMethod(),idOfServer);
	if(clients[fd].getMethod() == "GET")
		get(*this, ind, fd);
	else if(clients[fd].getMethod() == "POST")
		post(*this, ind, fd);
	else if(clients[fd].getMethod() == "DELETE")
		deleteM(*this, ind, fd);
	// std::cout <<"size of body " << clients[fd].getBody().size() << std::endl;

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

std::string Box::makeResponse(int fd, std::string value)
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
	char buffer[2048] = {0};
	int bytesRead = recv(fdRequest, buffer, 2047, 0);
	std::cout << "bytes read : " << bytesRead << "\n";
	// if ()
	// {
	// 	/* code */
	// }
	if (bytesRead <= 0)
	{
		std::cout << "Client disconnected." << std::endl;
		close(fdRequest);
		epoll_ctl(epollFd, EPOLL_CTL_DEL, fdRequest, 0);
	}
	else
	{
		std::string buff(buffer ,bytesRead);
		if (clients[fdRequest].getLoadingHeader())
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

void Box::sendResponse(int fd)
{
	signal(SIGPIPE,SIG_IGN);
	std::string countent;
	Response &a = clients[fd].getResponse();
	const int bufferSize = 1024;
    char buffer[bufferSize] = {0};
	if (!a.getStatustCgi())
	{
		if (!a.getStatusHeader())
		{
			countent = a.getHeader();
			a.openFile(a.getPathFile());
			a.setStatusHeader(true);
			send(fd,countent.c_str(),countent.length(),0);
		}
		if (a.getFile().is_open())
		{
			a.getFile().read(buffer, bufferSize - 1);
			std::streamsize bytesRead = a.getFile().gcount();
			if (bytesRead > 0)
			{
				std::string body(buffer, bytesRead);
				send(fd, body.c_str(), body.length(), 0);
			}
			if (a.getFile().eof())
			{
				close(fd);
				a.getFile().close();
			}
		}
		else if (!a.getBody().empty())
		{
			std::string body = a.getBody();
			send(fd, body.c_str(), body.length(), 0);
			close(fd);
			a.getFile().close();
		}
	}
	else if (a.getStatustCgi())
	{
		std::string response;
		if (!a.getStatusHeader())
		{
			a.openFile(a.getPathFile());
			response = "HTTP/1.1 200 OK \r\n";
		}
		if (a.getFile().is_open())
		{
			a.getFile().read(buffer, bufferSize - 1);
			std::streamsize bytesRead = a.getFile().gcount();
			std::string buff(buffer, bytesRead);
			size_t pos =  buff.find("\r\n\r\n");
			if(pos != std::string::npos && (buff.find("Set-Cookie:") != std::string::npos || buff.find("Content-type:") != std::string::npos))
			{
				buff = response  + buff;
				send(fd,buff.c_str(),buff.length(),0);
			}
			else if(!a.getStatusHeader())
			{
				buff = response  + "Content-type: text/html\r\n\r\n" + buff;
				send(fd,buff.c_str(),buff.length(),0);
			}
			else
				send(fd, buff.c_str(), buff.length(), 0);
			if (a.getFile().eof())
			{
				unlink(a.getPathFile().c_str());
				close(fd);
				a.getFile().close();
			}
		}
		a.setStatusHeader(true);
	}
	clients[fd].setResponse(a);
}

void Box::makeSocketNonBlocking(int sockfd)
{
	int flags = fcntl(sockfd, F_GETFL, 0);
	if (flags == -1)
	{
		perror("fcntl");
		return;
	}
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
		perror("fcntl");
}

void Box::timeOut(int fd, clock_t endTime)
{
	if (endTime - clients[fd].getTimeOut() == 5000000 && clients[fd].getLoadingHeader())
	{
		std::cout << "dkhal l time aout\n";
		throw errorMessage(504, clients[fd].getServerId());
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
	Response rep;
	int epollFd = epoll_create(1);
	  std::string res;
	_InfoServer = data;
	for (size_t i = 0; i < numberOfServer; i++)
	{
		int socket_server = socket(AF_INET,SOCK_STREAM,0);
		makeSocketNonBlocking(socket_server);
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
				clients[client_socket].setResponse(rep);
				this->_host = _InfoServer.getServer().at(d).getHost();
				this->_listen = _InfoServer.getServer().at(d).getListen();
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
				if (events[i].events & EPOLLIN && clients[events[i].data.fd].getResponse().getStatusResponse())
				{
					try
					{
						clients[events[i].data.fd].setTimeOut(clock());
						readRequest(events[i].data.fd, epollFd);
					}
					catch (const errorMessage& e)
					{
						clients[events[i].data.fd].getResponse().\
						setValues(false,events[i].data.fd,\
						e.getStatusCode(),\
						e.what(),\
						e.getType(),\
						e.getBody(),\
						e.getCgiStatus());
						clients[events[i].data.fd].setTimeOut(0);
						clients[events[i].data.fd].setMatchedTime(false);
					}
				}
				else if ((events[i].events & EPOLLOUT))
				{
					try
					{
						clock_t endTime =  clock();
						if (clients[events[i].data.fd].getTimeOut())
						{
							if (endTime - clients[events[i].data.fd].getTimeOut() >= 5000000 && clients[events[i].data.fd].getLoadingHeader())
							{
								throw errorMessage(504, clients[events[i].data.fd].getServerId());
							}
							else if (endTime - clients[events[i].data.fd].getTimeOut() >= 9000000)
							{
								throw errorMessage(504, clients[events[i].data.fd].getServerId());
							}
						}
					}
					catch(const errorMessage& e)
					{
						clients[events[i].data.fd].getResponse().\
						setValues(false,events[i].data.fd,\
						e.getStatusCode(),\
						e.what(),\
						e.getType(),\
						e.getBody(),\
						e.getCgiStatus());
						clients[events[i].data.fd].setTimeOut(0);
						clients[events[i].data.fd].setMatchedTime(false);
					}
					if (!clients[events[i].data.fd].getResponse().getStatusResponse())
					{
						sendResponse(events[i].data.fd);
					}
				}
			}
		}
	}
}

Box::~Box()
{
}

std::map<int,Client>& Box::getClients() {
	return this->clients;
}


webServer& Box::getWebServer() {
	return this->_InfoServer;
}

const std::string& Box::getQueryString() const
{
	return this->QueryString;
}

std::string Box::FullQueryString(std::string& path)
{
	size_t a = path.find_last_of('?');
	if (a != std::string::npos)
	{
		QueryString = path.substr(a + 1, path.length());
		std::cout << " QueryString " << QueryString << std::endl;
		return path.substr(0,a);
	}
	return path;
}
