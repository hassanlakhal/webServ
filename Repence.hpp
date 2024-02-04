/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Repence.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/04 19:54:25 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

class Repence
{
    private:
        bool status;
        int fd;
        int status_code;
        bool status_close;
        std::string header;
        std::string body;
        std::string path;
        std::string type;
        std::ifstream file;
        bool status_header;
    public:
        Repence();
        Repence(bool status,int fd, int status_code, std::string path);
        Repence& operator=(const Repence& other);
        Repence(const Repence& other);
        void setValues(bool status,int fd, int status_code, std::string path, std::string type,std::string content);
        void closeFile();
        bool getStatusRepence() const;
        void setStatusHeader(bool status_header);
        bool getStatusHeader() const;
        bool getStatusClinet() const;
        std::string getHeader();
        std::ifstream& getFile() ;
        std::string getBody();
        const std::string& getPathFile();
        void openFile(const std::string& path);
        // std::ifstream getFile() const;
        ~Repence();

};


