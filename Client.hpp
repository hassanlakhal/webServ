/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/28 21:13:36 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include<vector>
#include<algorithm>
#include"Repence.hpp"
// #include"parsingFile.hpp"
typedef std::map<std::string, std::string> infoMap;
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
        infoMap Map;
        Repence repence;
        // short port;
    public:
        Client();
        Client(int serverId);
        Client(const Client& other); 
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
        void setRepence(const Repence& rep);
        const Repence& getRepence() const;
        const infoMap getInfoMap() const;
        std::string trim(std::string& word);
        void ParsingRequest();
        ~Client();
};

#endif