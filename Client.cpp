/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:30 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/04 19:52:44 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"
#include"errorMessage.hpp"
#include"parsingFile.hpp"
Client::Client(): loadingHead(true),serverId(0)
{
	this->outfileOpened = false;
	this->EnteredfirstTime = false;
}

Client::Client(int serverId): loadingHead(true),serverId(serverId)
{
	this->outfileOpened = false;
	this->EnteredfirstTime = false;
	this->size = 0;
	this->sizeAppended = 0;
}

Client::~Client()
{
}

int Client::getServerId() const
{
	return this->serverId;
}

const Client& Client::getClinet() const
{
	return *this;
}

Client::Client(const Client& other)
{
	fullRequset = other.fullRequset;
	host = other.host;
	method = other.method;
	path = other.path;
	protocal = other.protocal;
	type = other.type;
	loadingHead = other.loadingHead;
	body = other.body;
	serverId = other.serverId;
	repence = other.repence;
	this->outfileOpened = other.outfileOpened;
	this->EnteredfirstTime = other.EnteredfirstTime;
	this->size = other.size;
	this->sizeAppended = other.sizeAppended;
}

Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		fullRequset = other.fullRequset;
		host = other.host;
		method = other.method;
		path = other.path;
		protocal = other.protocal;
		type = other.type;
		loadingHead = other.loadingHead;
		body = other.body;
		serverId = other.serverId;
		repence = other.repence;
		this->EnteredfirstTime = other.EnteredfirstTime;
		Map = other.Map;
		this->size = other.size;
		this->sizeAppended = other.sizeAppended;
	}
	return *this;
}

void Client::setRepence(const Repence& rep)
{
	this->repence = rep;
}

Repence& Client::getRepence()
{
	return this->repence;
}

void Client::setRequset(std::string& buff)
{
	fullRequset.append(buff);
}

std::string Client::getfullRequset() const
{
	return this->fullRequset;
}

const std::string& Client::getRequset() const
{
	return this->fullRequset;
}

const std::string& Client::getMethod() const
{
	// std::cout << method << std::endl;
	return this->method;
}

void Client::setStartLine(std::istringstream& iss)
{
	getline(iss,method,' ');
	getline(iss,path,' ');
	getline(iss,protocal, '\n');
}

void Client::loadingFormation(std::string& line)
{
	std::istringstream iss(line);
	std::string key ,value;
	while (getline(iss, key,':') && getline(iss,value))
	{
		Map[key] = trim(value);
	}
}

size_t Client::getSizeBody() const
{
	return this->size;
}

void Client::setBody(std::istringstream& buff)
{
	// this->stringBody = buff.str();
	std::istreambuf_iterator<char> begin(buff);
	std::istreambuf_iterator<char> end;
	body.assign(begin ,end);
	// body.insert(body.end() ,begin ,end);
	size += body.size();
}

bool Client::getLoadingHeader() const
{
	return this->loadingHead;
}

const std::vector<unsigned char>& Client::getBody() const
{
	return this->body;
}

std::string Client::getPath() const
{
	return this->path;
}

const std::string& Client::getStringBody() const{
	return this->stringBody;
}

void Client::setStringBody(char c, std::string str){
	if(c == 'a')
		this->stringBody.append(str);
	else
		this->stringBody = str;
}


std::string Client::trim(std::string& word)
{
	size_t first = word.find_first_not_of(" ");
	if (first == std::string::npos)
		return word;
	size_t last = word.find_last_not_of(" ");
	return word.substr(first, last - first + 1);
}

const infoMap Client::getInfoMap() const
{
	return this->Map;
}

void Client::ParsingRequest()
{
	std::istringstream iss(this->fullRequset, std::ios::binary);
	std::string line;
	std::string temp;
	webServer wserv = getMyServer();
	long long nb = 0;
	if (loadingHead)
	{
		setStartLine(iss);
		while (getline(iss, line,'\r')  && getline(iss, temp) && !line.empty())
		{
			loadingFormation(line);
		}
		setBody(iss);
		std::istringstream iss(Map["Content-Length"]);
		iss >> nb;
		// std::cout << "Content-Length " << nb << std::endl;
		if (method == "POST")
		{
			if(Map["Content-Length"] == "0" || Map["Content-Length"].empty())
				throw errorMessage(400,serverId);
		}
		if (!Map["Transfer-Encoding"].empty() && Map["Transfer-Encoding"] != "chunked")
			  throw errorMessage(501,serverId);
		if (path.find("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~!$&'()*+,;=") != std::string::npos)
			throw  errorMessage(400,serverId);
		if (Map["Host"].length() + path.length() > 2048)
			   throw errorMessage(414,serverId);
		if (nb > wserv.getServer()[serverId].getMaxBodySize())
			throw errorMessage(413,serverId);
		loadingHead = false;
	}
}


void Client::openFile(std::string file){
	this->outfile.open(file.c_str());
	if(!outfile.is_open()){
		//throw
	}
	this->outfileOpened = true;
}

std::ofstream& Client::getOutFile() {
	return this->outfile;
}
bool Client::getOutFileOpened() const{
	return this->outfileOpened;
}


bool Client::getEnteredfirstTime() const
{
	return this->EnteredfirstTime;
}

void Client::setEnteredfirstTime(bool b)
{
	this->EnteredfirstTime = b;
}

unsigned long Client::getChunkSizee() const{
	return this->ChunkSizee;
}

void Client::setChunkSizee(unsigned long s){
	this->ChunkSizee = s;
}

size_t Client::getSizeAppended() const{
	return this->sizeAppended;
}

void Client::setSizeAppended(size_t s){
	this->sizeAppended += s;
}
