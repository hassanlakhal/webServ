/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:54 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <sstream>
#include <fstream>
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
        std::string stringBody;
        std::ofstream outfile;
        bool outfileOpened;
        bool EnteredfirstTime;
        bool loadingHead;
        int serverId;
        unsigned long ChunkSizee;
        std::vector<unsigned char> body;
        infoMap Map;
        size_t size;
        size_t sizeAppended;
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
        const std::string& getStringBody() const;
        unsigned long getChunkSizee() const;
        void setChunkSizee(unsigned long s);
        void setStringBody(char c, std::string str);
        void setRepence(const Repence& rep);
        Repence& getRepence();
        void openFile(std::string file);
        const infoMap getInfoMap() const;
        std::ofstream& getOutFile();
        bool getOutFileOpened() const;
        bool getEnteredfirstTime() const;
        void setEnteredfirstTime(bool b);
        size_t getSizeBody() const;
        size_t getSizeAppended() const;
        void setSizeAppended(size_t s);
        std::string trim(std::string& word);
        void ParsingRequest();
        ~Client();
};

#endif
