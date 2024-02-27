/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:30 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/27 15:44:11 by eej-jama         ###   ########.fr       */
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
	this->detectCgi = false;
	this->pathInfoChecker = false;
	this->sizeCompard = 0;
}

Client::Client(int serverId): loadingHead(true),serverId(serverId)
{
	this->outfileOpened = false;
	this->EnteredfirstTime = false;
	this->matchedTime = false;
	this->detectCgi = false;
	this->size = 0;
	this->sizeAppended = 0;
	this->start_time = clock();
	this->pathInfoChecker = false;
	this->sizeCompard = 0;
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
	this->detectCgi = other.detectCgi;
	this->pathInfoChecker = other.pathInfoChecker;
	this->sizeCompard = other.sizeCompard;
	QueryString = other.QueryString;

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
		this->detectCgi = other.detectCgi;
		this->pathInfoChecker = other.pathInfoChecker;
		QueryString = other.QueryString;
		this->sizeCompard = other.sizeCompard;
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
	return this->method;
}

void Client::setStartLine(std::istringstream& iss)
{
	getline(iss,method,' ');
	getline(iss,path,' ');
	getline(iss,protocal, '\n');
}

std::string  Client::getProtocal()
{
	return this->protocal;
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
	if (loadingHead)
	{
		setStartLine(iss);
		while (getline(iss, line,'\r')  && getline(iss, temp) && !line.empty())
		{
			loadingFormation(line);
		}
		setBody(iss);
		loadingHead = false;
	}
}


void Client::openFile(std::string file){
	this->outfile = std::fopen(file.c_str(), "a+");
	if(!this->outfile){
		throw errorMessage(500, this->serverId);
	}
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

void Client::setDetectCgi(bool b){
	this->detectCgi = b;
}

bool Client::getDetectCgi(){
	return this->detectCgi;
}

void Client::setStatusChild(int i){
	this->statusChild = i;
}

int Client::getPidChild(){
	return this->pidChild;
}

int Client::getStatusChild(){
	return this->statusChild;
}

void Client::setPidChild(int i){
	this->pidChild = i;
}

void Client::setSavedReqPath(std::string str){
	this->savedReqPath = str;
}
void Client::setSavedFile(std::string str){
	this->savedFile = str;
}
void Client::setSavedServerID(int i){
	this->savedServerID = i;
}
void Client::setSavedMethod(std::string str){
	this->savedMethod = str;
}
void Client::setSavedPostFIle(std::string str){
	this->savedPostFile = str;
}
std::string Client::getSavedReqPath(){
	return this->savedReqPath;
}
std::string Client::getSavedFile(){
	return this->savedFile;
}
int Client::getSavedServerID(){
	return this->savedServerID;
}
std::string Client::getSavedMethod(){
	return this->savedMethod;
}
std::string Client::getSavedPostFIle(){
	return this->savedPostFile;
}

void Client::setLocation(Location& loc){
	this->savedLocation = loc;
}

Location& Client::getLocation(){
	return this->savedLocation;
}

void Client::setSavedDileDel(std::string str){
	this->savedFileDel = str;
}

std::string Client::getSavedFileDel(){
	return this->savedFileDel;
}

std::string Client::FullQueryString(std::string& path)
{
	size_t a = path.find_last_of('?');
	if (a != std::string::npos)
	{
		QueryString = path.substr(a + 1, path.length());
		return path.substr(0,a);
	}
	return path;
}

const std::string& Client::getQueryString() const
{
	return this->QueryString;
}

void Client::setStartTimeCGI(clock_t start_time){
	this->StartTimeCGI = start_time;
}

clock_t Client::getStartTimeCGI(){
	return this->StartTimeCGI;
}

void Client::setPathInfo(std::string req){

	//path : www/folder/lopos
	struct stat file_stat;
	if(req.empty()){
		this->pathInfo = "";
		setPathInfoChecker(true);
		return;
	}

	if(stat(req.c_str(), &file_stat) != 0){
		std::string s;
		if(req.find("/") != std::string::npos){
			s = req.substr(0, req.find_last_of("/"));
			setPathInfo(s);
			if(!getPathInfoChecker())
				this->pathInfo.append(req.substr(req.find_last_of("/")));
			else
				this->pathInfo = "";
		}
	}
	else
	{
		if(!S_ISDIR(file_stat.st_mode))
			return;
		else{
			this->pathInfo = "";
			setPathInfoChecker(true);
			return;
		}
	}
}

std::string Client::getPathInfo(){
	return this->pathInfo;
}

void Client::setPathInfoChecker(bool b){
	this->pathInfoChecker = b;
}

bool Client::getPathInfoChecker(){
	return this->pathInfoChecker;
}

void Client::setSizeCompared(size_t s){
	this->sizeCompard += s;
}

size_t Client::getSizeCompared(){
	return this->sizeCompard;
}
