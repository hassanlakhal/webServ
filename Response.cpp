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

void Response::setValues(bool status,int fd, int status_code, std::string path, std::string type,std::string content)
{
    this->status = status;
    this->status_code = status_code;
    this->path = path;
    this->fd = fd;
    this->type = type;
    this->body = content;
}

bool Response::getStatusResponse() const
{
    return this->status;
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
    start_line = "HTTP/1.1 " + result + " OK" + "\r\n";
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
    status_header = other.status_header;
    if (file.is_open())
        file.close();
    if (other.file.is_open())
        file.open(other.path.c_str(), std::ios::in | std::ios::binary);
}