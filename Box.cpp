/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:45 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/28 00:33:51 by hlakhal-         ###   ########.fr       */
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
	std::stack<int> ind;
	for (size_t i = 0; i < loc.size(); ++i)
	{
		hashTable.push_back(std::make_pair(loc[i].getPath(), i));
	}
	for (size_t i = 0; i < hashTable.size(); ++i)
	{
		if (hashTable[i].first == path)
		{
			std::string PathLoc = loc[i].getRoot() + hashTable[i].first;
			std::ifstream file;
			file.open(PathLoc.c_str(), std::ios::in | std::ios::binary);
			if (file.is_open())
			{
				file.close();
				ind.push(i);
				continue;
			}
			return hashTable[i].second;
		}
	}
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
		if (ind.size() > 0)
			return ind.top();
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
	else
		throw errorMessage(501,id);
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
	for (; i < posServer.size(); ++i)
	{
		std::vector<std::string> names = sr[posServer[i]].getServerName();
		std::vector<std::string>::iterator it = find(names.begin(),names.end(),name);
		if(it != names.end())
		{
			i = posServer[i];
			return true;
		}
	}
	return false;
}


void Box::sendRequest(int fd)
{
	int idOfServer = 0;
	std::string pathLocation;
	idOfServer = clients[fd].getServerId();
	std::vector<Location> loc = _InfoServer.getServer()[idOfServer].getLocation();
	if(!clients[fd].getMatchedTime())
	{
		std::string path = clients[fd].getPath();
		path = removeSlach(path);
		path = clients[fd].FullQueryString(path);
		int ind = matchLocation(loc,path,idOfServer);
		if (ind == -1)
			throw errorMessage(404,idOfServer);
		clients[fd].setPathLoc(path);
		pathLocation = loc[ind].getRoot() + "/" + path.substr(loc[ind].getPath().length());
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
	clients[fd].setPathInfo(clients[fd].getPath());
	if(!clients[fd].getPathInfo().empty()){
		if(clients[fd].getPath().find(clients[fd].getPathInfo()) != std::string::npos){
			clients[fd].setPath(clients[fd].getPath().substr(0, clients[fd].getPath().rfind(clients[fd].getPathInfo())));
			clients[fd].setPathLoc(clients[fd].getPathLoc().substr(0, clients[fd].getPathLoc().rfind(clients[fd].getPathInfo())));
		}
	}
	if(clients[fd].getMethod() == "GET")
		get(*this, ind, fd);
	else if(clients[fd].getMethod() == "POST")
		post(*this, ind, fd);
	else if(clients[fd].getMethod() == "DELETE")
		deleteM(*this, ind, fd);
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

bool isNumber(int idOfServer, std::map<std::string, std::string>& info)
{
	std::map<std::string, std::string>::iterator it;
	it = info.find("Content-Length");
	if(it != info.end())
	{
		std::string s = info["Content-Length"];
		if (s.empty())
			throw errorMessage(400, idOfServer);
		for (size_t i = 0; i < s.length(); ++i)
		{
			if (!isdigit(s[i]))
				throw errorMessage(400, idOfServer);
		}
		return false;
	}
	else
	{
		it = info.find("Transfer-Encoding");
		if(it == info.end())
			throw errorMessage(400, idOfServer);
	}
    return true;
}

void Box::readRequest(int fdRequest, int epollFd)
{
	char buffer[2048] = {0};
	int idOfServer = 0;
	double nb = 0;
	int bytesRead = recv(fdRequest, buffer, 2047, 0);
	if (bytesRead <= 0)
	{
		if (clients[fdRequest].getDetectCgi())
		{
			int status;
			kill(clients[fdRequest].getPidChild(),SIGKILL);
			waitpid(clients[fdRequest].getPidChild(),&status,0);
			if (unlink(clients[fdRequest].getSavedFileDel().c_str()) == -1)
				throw errorMessage(500, clients[fdRequest].getSavedServerID());
		}
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
			{
				clients[fdRequest].ParsingRequest();
				std::map<std::string, std::string> mapInfo = clients[fdRequest].getInfoMap();
				std::vector<int> posServer;
				if(checkDup(_InfoServer.getServer(),posServer))
				{
					size_t  i = 0;
					std::istringstream iss(mapInfo["Host"]);
					std::string host;
					getline(iss,host,':');
					if (checkName(_InfoServer.getServer(), host,i,posServer))
						idOfServer = i;
				}
				else
					idOfServer = clients[fdRequest].getServerId();
				clients[fdRequest].setServerId(idOfServer);
				if (clients[fdRequest].getMethod().empty() || clients[fdRequest].getProtocal().empty() || clients[fdRequest].getPath().empty() || clients[fdRequest].getProtocal() != "HTTP/1.1\r")
					throw errorMessage(400,idOfServer);
				if (mapInfo["Host"].empty())
					throw errorMessage(400,idOfServer);
				if (clients[fdRequest].getMethod() == "POST")
				{
					bool isI =  isNumber(idOfServer,mapInfo);
					if (!isI)
					{
						std::istringstream iss(mapInfo["Content-Length"]);
						iss >> nb;
					}
					if (nb > _InfoServer.getServer()[idOfServer].getMaxBodySize() || _InfoServer.getServer()[idOfServer].getMaxBodySize() == 0)
						throw errorMessage(413,idOfServer);
					if (!mapInfo["Transfer-Encoding"].empty() && mapInfo["Transfer-Encoding"] != "chunked")
						throw errorMessage(501,idOfServer);
				}

				if (clients[fdRequest].getPath().find("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~!$&'()*+,;=") != std::string::npos)
					throw  errorMessage(400,idOfServer);
				if (mapInfo["Host"].length() + clients[fdRequest].getPath().length() > 2048)
					throw errorMessage(414,idOfServer);
			}
			else
			{
				std::istringstream iss(buff);
				clients[fdRequest].setBody(iss);
			}
			sendRequest(fdRequest);
		}
	}
}

std::string Box::generetPage(int status, std::map<int, std::string> httpMessage)
{
	std::stringstream iss;
	std::string statString;
	iss << status;
	statString = iss.str();
	std::string message = httpMessage[status];
	std::string html = "<html>\n";
	html += "<head>\n";
	html += "<title>" + statString + "</title>\n";
	html += "</head>\n";
	html += "<body>\n";
	html += "<h1 style=\"text-align: center;\">"+ statString +"</h1>\n";
	html += "<p style=\"text-align: center;\"> " + message + "</p>\n";
	html += "</body>\n";
	html += "</html>\n";
	return html;
}

void Box::sendResponse(int fd)
{
	signal(SIGPIPE,SIG_IGN);
	std::string mess;
	std::string countent;
	ssize_t sendByte;
	std::map<int, std::string> httpMessage;
	Response &a = clients[fd].getResponse();
	const int bufferSize = 1024;
    char buffer[bufferSize] = {0};
	httpMessage = a.getHttpStatusMessages();
	mess = httpMessage[a.getStatusCode()];
	if (!a.getStatustCgi())
	{
		if (!a.getStatusHeader())
		{
			countent = a.getHeader();
			a.openFile(a.getPathFile());
			a.setStatusHeader(true);
			sendByte = send(fd,countent.c_str(),countent.length(),0);
			if (sendByte <= 0)
			{
				close(fd);
				a.getFile().close();
			}
			if(a.getStatusCode() == 301 || a.getStatusCode() == 204)
					std::cout << GREEN << a.getStatusCode() << mess <<  RESET << std::endl;
			if (a.getStatusCode() == 204)
			{
				close(fd);
				a.getFile().close();
				return ;
			}
			return ;
		}
		if (a.getFile().is_open())
		{
			a.getFile().read(buffer, bufferSize - 1);
			std::streamsize bytesRead = a.getFile().gcount();
			if (bytesRead > 0)
			{
				std::string body(buffer, bytesRead);
				sendByte = send(fd, body.c_str(), body.length(), 0);
				if (sendByte <= 0)
				{
					close(fd);
					a.getFile().close();
				}
			}
			if (a.getFile().eof())
			{
				close(fd);
				a.getFile().close();
				if(a.getStatusCode() == 200 || a.getStatusCode() == 201 || a.getStatusCode() == 301 || a.getStatusCode() == 204 )
					std::cout << GREEN << a.getStatusCode() << mess <<  RESET << std::endl;
				else
					std::cout << RED << a.getStatusCode() << mess << RESET << std::endl;
			}
		}
		else if (!a.getBody().empty())
		{
			std::string body = a.getBody();
			sendByte = send(fd, body.c_str(), body.length(), 0);
			if (sendByte <= 0)
			{
				close(fd);
				a.getFile().close();
				return ;
			}
			close(fd);
			a.getFile().close();
			if(a.getStatusCode() == 200 || a.getStatusCode() == 201 || a.getStatusCode() == 301 || a.getStatusCode() == 204)
				std::cout << GREEN << a.getStatusCode() << mess <<  RESET << std::endl;
			else
				std::cout << RED << a.getStatusCode() << mess << RESET << std::endl;
		}
		else
		{
			std::string html = generetPage(a.getStatusCode(),httpMessage);
			sendByte = send(fd,html.c_str(), html.size(),0);
			if (sendByte <= 0)
			{
				close(fd);
				return ;
			}
			close(fd);
			return;
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
				sendByte = send(fd,buff.c_str(),buff.length(),0);
				if (sendByte <= 0)
				{
					close(fd);
					a.getFile().close();
				}

			}
			else if(!a.getStatusHeader())
			{
				buff = response  + "Content-type: text/html\r\n\r\n" + buff;
				sendByte = send(fd,buff.c_str(),buff.length(),0);
				if (sendByte <= 0)
				{
					close(fd);
					a.getFile().close();
				}
			}
			else
			{
				sendByte = send(fd,buff.c_str(),buff.length(),0);
				if (sendByte <= 0)
				{
					close(fd);
					a.getFile().close();
				}

			}
			if (a.getFile().eof())
			{
				unlink(a.getPathFile().c_str());
				close(fd);
				a.getFile().close();
				if(a.getStatusCode() == 200 || a.getStatusCode() == 201 || a.getStatusCode() == 301 || a.getStatusCode() == 204)
					std::cout << GREEN << a.getStatusCode() << mess << RESET << std::endl;
				else
					std::cout << RED << a.getStatusCode() << " OK" << RESET << std::endl;
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
		if (socket_server < 0)
			throw std::runtime_error("Error\ncan not open this socket");
		int reuseaddr = 1;
		if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuseaddr, sizeof(int)) < 0)
		{
			throw std::runtime_error("Error\nsetting SO_REUSEADDR option");
		}
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
		for (int i = 0; i < numEvents; i++)
		{
			if ((it = std::find(fds.begin(),fds.end(),events[i].data.fd)) != fds.end())
			{
				d = it - fds.begin();
				client_socket = accept(events[i].data.fd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_addrlen);
				if (client_socket < 0)
				{
					perror("accept ");
					continue;
				}
				makeSocketNonBlocking(client_socket);
				Client client(d);
				if (clients.find(client_socket) != clients.end())
					clients.erase(client_socket);
				clients[client_socket] = client;
				clients[client_socket].setResponse(rep);
				this->_host = _InfoServer.getServer().at(d).getHost();
				this->_listen = _InfoServer.getServer().at(d).getListen();
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
				else if(clients[events[i].data.fd].getDetectCgi()){
					try
					{
						int fd = events[i].data.fd;
						std::string reqPath = clients[fd].getSavedReqPath();
						std::string file = clients[fd].getSavedFile();
						int serverID = clients[fd].getSavedServerID();
						std::string method = clients[fd].getSavedMethod();
						std::string postFile= clients[fd].getSavedPostFIle();
						cgi(clients[fd], clients[fd].getLocation(),reqPath, file, serverID, method, postFile);
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
								close(events[i].data.fd);
							}
							else if (endTime - clients[events[i].data.fd].getTimeOut() >= 9000000)
							{
								if (clients[events[i].data.fd].getMethod() == "POST")
								{
									fclose(clients[events[i].data.fd].getOutFile());
									clients[events[i].data.fd].setOutFileOpened(false);
								}
								throw errorMessage(408, clients[events[i].data.fd].getServerId());
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

// std::string Box::FullQueryString(std::string& path)
// {
// 	size_t a = path.find_last_of('?');
// 	if (a != std::string::npos)
// 	{
// 		QueryString = path.substr(a + 1, path.length());
// 		return path.substr(0,a);
// 	}
// 	return path;
// }
