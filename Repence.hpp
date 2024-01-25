/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Repence.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:34:24 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/25 23:36:54 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include<cstdlib>
#include<cstring>
#include <unistd.h>
#include <csignal>

class Repence
{
    private:
        bool status;
        int fd;
        int status_code;
        std::string header;
        std::string body;
        std::string path;
        std::ifstream file;
    public:
        Repence();
        Repence(bool status,int fd, int status_code, std::string path);
        Repence& operator=(const Repence& other);
        Repence(const Repence& other);
        void setValues(bool status,int fd, int status_code, std::string path);
        void sendRepence(int fd);
        bool getStatusRepence() const;
        // std::ifstream getFile() const;
        ~Repence();
        
};


