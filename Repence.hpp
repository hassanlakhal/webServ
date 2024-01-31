/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Repence.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/31 11:08:33 by hlakhal-         ###   ########.fr       */
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
        void sendRepence(int fd);
        void closeFile(); 
        bool getStatusRepence() const;
        bool getStatusClinet() const;
        // std::ifstream getFile() const;
        ~Repence();
        
};


