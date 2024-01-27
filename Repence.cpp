/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Repence.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/27 15:32:27 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Repence.hpp"

Repence::Repence()
{
    this->status = true;
}

Repence::Repence(bool status,int fd, int status_code, std::string path)
{
    this->status = status;
    this->status_code = status_code;
    this->path = path;
    this->fd = fd;
}

bool Repence::getStatusClinet() const
{
    return this->status_close;
}

void Repence::sendRepence(int fd)
{
    const int bufferSize = 1024;
    char buffer[bufferSize] = {0};
    std::string start_line, header, result, name_server, location;
    signal(SIGPIPE,SIG_IGN);
    std::stringstream ss;
    ss << this->status_code;
    result = ss.str();
    if (status_header)
    {
        name_server = "test";
        if (result == "301")
            location = "Location: " + this->path + "\r\n";
        start_line = "HTTP/1.0 " + result + " error " + "\r\n";
        header = "Server: " + name_server + "\r\n" + "Content-type: text/html\r\n" + location + "\r\n";
        status_header = false;
    }
    if (result != "200")
    {
        file.read(buffer, bufferSize);
        std::string body(buffer, sizeof(buffer));
        std::string buff = start_line + header + body;
        write(fd, buff.c_str(), strlen(buff.c_str()));
        if (file.eof())
        {
            close(fd);
            file.close();
            body.clear();
        }
    }
}

void Repence::closeFile() 
{
    this->file.close();
}

void Repence::setValues(bool status,int fd, int status_code, std::string path)
{
    this->status = status;
    this->status_code = status_code;
    this->path = path;
    this->fd = fd;
    this->file.open(path.c_str(), std::ios::binary);
    this->status_header = true;
    // this->file = file;
    // opening path  
}

// std::ifstream Repence::getFile() const
// {
   
//     return file;
// }

bool Repence::getStatusRepence() const
{
    return this->status;
}

Repence::~Repence()
{
}

Repence& Repence::operator=(const Repence& other)
{
    if (this != &other)
    {
        status = other.status;
        fd = other.fd;
        status_code = other.status_code;
        header = other.header;
        body = other.body;
    }
    return *this;
}

Repence::Repence(const Repence& other)
{
    status = other.status;
    fd = other.fd;
    status_code = other.status_code;
    header = other.header;
    body = other.body;
}