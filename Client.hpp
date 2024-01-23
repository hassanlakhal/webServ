/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/23 11:18:41 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include<vector>
// #include"parsingFile.hpp"
class Client
{
    private:
        std::string fullRequset;
        std::string host;
        std::string method;
        std::string path;
        std::string protocal;
        std::string type;
        bool loadingHead;
        int serverId;
        std::vector<unsigned char> body;
        // short port;
    public:
        Client();
        Client(int serverId);
        void setRequset(std::string& buff);
        const std::string& getRequset() const;
        const std::string& getMethod() const;
        int getServerId() const;
        void setStartLine(std::istringstream& iss);
        const Client& getClinet() const;
        bool getLoadingHeader() const;
        std::string getPath() const;
        void loadingFormation(std::string& line);
        void setBody(std::istringstream& buff);
        Client& operator=(const Client& other);
        std::string getfullRequset() const ;
        const std::vector<unsigned char>& getBody() const;
        void ParsingRequest();
        ~Client();
};

#endif