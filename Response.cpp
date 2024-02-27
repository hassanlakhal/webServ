/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/04 19:54:45 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Response.hpp"

Response::Response()
{
    this->status_header = false;
    this->status = true;
    HttpStatusMessages[200] = " OK";
    HttpStatusMessages[201] = " Created";
    HttpStatusMessages[204] = " No Content";
    HttpStatusMessages[301] = " Moved Permanently";
    HttpStatusMessages[400] = " Bad Request";
    HttpStatusMessages[401] = " Unauthorized";
    HttpStatusMessages[402] = " Payment Required";
    HttpStatusMessages[403] = " Forbidden";
    HttpStatusMessages[404] = " Not Found";
    HttpStatusMessages[405] = " Method Not Allowed";
    HttpStatusMessages[408] = " Request Timeout";
    HttpStatusMessages[413] = " Request Entity Too Large";
    HttpStatusMessages[500] = " Internal Server Error";
    HttpStatusMessages[501] = " Not Implemented";
    HttpStatusMessages[502] = " Bad Gateway";
    HttpStatusMessages[503] = " Service Unavailable";
    HttpStatusMessages[504] = " Gateway Timeout";
    HttpStatusMessages[505] = " HTTP Version Not Supported";
}

Response::Response(bool status,int fd, int status_code, std::string path)
{
    this->status_header = false;
    this->status = status;
    this->status_code = status_code;
    this->path = path;
    this->fd = fd;
}

bool Response::getStatusClinet() const
{
    return this->status_close;
}

void Response::setStatusHeader(bool status_header)
{
    this->status_header = status_header;
}

const std::string& Response::getPathFile()
{
    return this->path;
}

void Response::openFile(const std::string& path)
{
    file.open(path.c_str(), std::ios::in | std::ios::binary);
}

std::ifstream& Response::getFile()
{
    return this->file;
}

std::string Response::getBody()
{
    return this->body;
}

void Response::closeFile()
{
    this->file.close();
}

void Response::setValues(bool status,int fd, int status_code, std::string path, std::string type,std::string content, bool isCgi)
{
    this->status = status;
    this->status_code = status_code;
    this->path = path;
    this->fd = fd;
    this->type = type;
    this->body = content;
    this->isCgi = isCgi;
}

bool Response::getStatusResponse() const
{
    return this->status;
}

int Response::getStatusCode() const
{
    return this->status_code;
}

Response::~Response()
{
}

std::string Response::getHeader()
{
    std::string start_line, header, result,cache, name_server, location;
    std::stringstream ss;
    ss << this->status_code;
    result = ss.str();
    name_server = "test";
    if (result == "301" || result == "201")
        location =  "\r\nLocation: " + this->path;
    if (result == "204")
    {
        start_line = "HTTP/1.1 " + result + HttpStatusMessages[status_code] +"\r\n";
        header = "Server: YourServer\r\n";
        header += "Content-Length: 0\r\n";
        header += "\r\n"; 
        return start_line + header;
    }
    start_line = "HTTP/1.1 " + result + HttpStatusMessages[status_code] + "\r\n";
    header = "Server: " + name_server + "\r\n" + "Content-Type: " + type + location  + "\r\n\r\n";
    start_line += header;
    return start_line;
}

Response& Response::operator=(const Response& other)
{
    if (this != &other)
    {
        status = other.status;
        fd = other.fd;
        status_code = other.status_code;
        status_close = other.status_close;
        header = other.header;
        body = other.body;
        path = other.path;
        type = other.type;
        this->isCgi = other.isCgi;
        status_header = other.status_header;
        if (file.is_open())
            file.close();
        if (other.file.is_open())
            file.open(other.path.c_str(), std::ios::in | std::ios::binary);
    }
    return *this;
}

bool Response::getStatusHeader() const
{
    return this->status_header;
}

bool Response::getStatustCgi() const
{
    return this->isCgi;
}

Response::Response(const Response& other)
{
    status = other.status;
    fd = other.fd;
    status_code = other.status_code;
    status_close = other.status_close;
    header = other.header;
    body = other.body;
    path = other.path;
    type = other.type;
    this->isCgi = other.isCgi;
    status_header = other.status_header;
    if (file.is_open())
        file.close();
    if (other.file.is_open())
        file.open(other.path.c_str(), std::ios::in | std::ios::binary);
}
const std::map<int, std::string>& Response::getHttpStatusMessages() const
{
    return HttpStatusMessages;
}
