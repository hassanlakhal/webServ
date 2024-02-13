/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:30 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/13 18:12:59 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"
#include"errorMessage.hpp"
#include"parsingFile.hpp"
Client::Client(): loadingHead(true),serverId(0)
{
	this->outfileOpened = false;
	this->EnteredfirstTime = false;
	this->matchedTime = false;
}

Client::Client(int serverId): loadingHead(true),serverId(serverId)
{
	this->outfileOpened = false;
	this->EnteredfirstTime = false;
	this->matchedTime = false;
	this->size = 0;
	this->sizeAppended = 0;
	this->start_time = clock();
}

int Client::incremetedFileName = 0;

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
	response = other.response;
	this->outfileOpened = other.outfileOpened;
	this->EnteredfirstTime = other.EnteredfirstTime;
	this->size = other.size;
	this->sizeAppended = other.sizeAppended;
	this->start_time = other.start_time;
	this->matchedTime = other.matchedTime;
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
		response = other.response;
		this->EnteredfirstTime = other.EnteredfirstTime;
		this->matchedTime = other.matchedTime;
		Map = other.Map;
		this->size = other.size;
		this->sizeAppended = other.sizeAppended;
		this->start_time = other.start_time;
	}
	return *this;
}

void Client::setResponse(const Response& rep)
{
	this->response = rep;
}

clock_t Client::getTimeOut()
{
	return this->start_time;
}

void Client::setTimeOut(clock_t start_time)
{
	this->start_time = start_time;
}
Response& Client::getResponse()
{
	return this->response;
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
	if (method.empty() || protocal.empty() || path.empty() || protocal != "HTTP/1.1\r")
		throw errorMessage(400,serverId);
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
	std::istreambuf_iterator<char> begin(buff);
	std::istreambuf_iterator<char> end;
	body.assign(begin ,end);
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

std::string Client::getPath()
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

infoMap Client::getInfoMap() const
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
		if (method == "POST")
		{
			if(Map["Content-Length"].empty())
				throw errorMessage(400,serverId);
		}
		if (Map["Host"].empty())
			throw errorMessage(400,serverId);
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
	this->outfile = std::fopen(file.c_str(), "a+");
	if(!this->outfile)
		throw errorMessage(500, this->serverId);
	this->outfileOpened = true;
	this->filePath = file;
}

FILE * Client::getOutFile() {
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

void Client::setSizeAppended(char c, size_t s){
	if(c == 'a')
		this->sizeAppended += s;
	else
		this->sizeAppended = s;
}

void Client::setOutFileOpened(bool b){
	this->outfileOpened = b;
}

void Client::setPath(const std::string& path)
{
	this->path = path;
}

void Client::setPathLoc(std::string loc){
	this->pathLoc = loc;
}

std::string Client::getFilePath(){
	return this->filePath;
}


std::string Client::getPathLoc(){
	return this->pathLoc;
}

bool Client::getMatchedTime(){
	return this->matchedTime;
}

void Client::setMatchedTime(bool b){
	this->matchedTime = b;
}

void Client::setInd(int ind){
	this->ind = ind;
}


int Client::getInd(){
	return this->ind;
}

void Client::setServerId(int serverId)
{
	this->serverId = serverId;
}

int Client::getIncremetedFileName(){
	return this->incremetedFileName;
}
void Client::IncremetedFileName(){
	this->incremetedFileName++;
}
