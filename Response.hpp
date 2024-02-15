/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/04 19:54:25 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <csignal>
#include <sstream>
#include <fcntl.h>
#include <sys/socket.h>
#include <map>

class Response
{
    private:
        bool status;
        int fd;
        int status_code;
        bool status_close;
        bool isCgi;
        std::string header;
        std::string body;
        std::string path;
        std::string type;
        std::ifstream file;
        bool status_header;
        std::map<int, std::string> HttpStatusMessages;
    public:
        Response();
        Response(bool status,int fd, int status_code, std::string path);
        Response& operator=(const Response& other);
        Response(const Response& other);
        void setValues(bool status,int fd, int status_code, std::string path, std::string type,std::string content, bool isCgi);
        void closeFile();
        bool getStatusResponse() const;
        void setStatusHeader(bool status_header);
        bool getStatusHeader() const;
        bool getStatusClinet() const;
        bool getStatustCgi() const;
        std::string getHeader();
        std::ifstream& getFile() ;
        int getStatusCode() const;
        std::string getBody();
        const std::string& getPathFile();
        void openFile(const std::string& path);
        const std::map<int, std::string>& getHttpStatusMessages() const;
        ~Response();

};

#endif

