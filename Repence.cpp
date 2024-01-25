/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Repence.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/25 23:52:30 by hlakhal-         ###   ########.fr       */
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

void Repence::sendRepence(int fd)
{
    signal(SIGPIPE,SIG_IGN);
    const int bufferSize = 1024;
    char buffer[bufferSize] = {0};
    std::ifstream file(path.c_str(), std::ios::binary);
    std::cout << fd << std::endl;
    while (file.read(buffer, bufferSize - 1)) 
    {
        if (int a = write(fd,buffer, file.gcount()))
        {
            // break ;
            // exit(12);
        }
    }
    write(fd,buffer, file.gcount());
    file.close();
}

void Repence::setValues(bool status,int fd, int status_code, std::string path)
{
    this->status = status;
    this->status_code = status_code;
    this->path = path;
    this->fd = fd;
    // std::ifstream file(path.c_str(), std::ios::binary);
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