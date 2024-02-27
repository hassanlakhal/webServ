/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/27 14:34:49 by eej-jama         ###   ########.fr       */
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
#include <algorithm>
#include "Response.hpp"
#include"Location.hpp"
#include <sys/stat.h>



typedef std::map<std::string, std::string> infoMap;
class Client
{
    private:
        std::string fullRequset;
        std::string host;
        std::string method;
        std::string path;
        std::string pathLoc;
        std::string filePath;
        std::string pathInfo;
        bool pathInfoChecker;
        std::string protocal;
        std::string type;
        std::string stringBody;
        int pidChild;
        int statusChild;
        int ind;
        static int incremetedFileName;
        FILE * outfile;
        bool outfileOpened;
        bool EnteredfirstTime;
        bool matchedTime;
        bool detectCgi;
        bool loadingHead;
        int serverId;
        unsigned long ChunkSizee;
        unsigned long sizeCompard;
        std::vector<unsigned char> body;
        infoMap Map;
        size_t size;
        size_t sizeAppended;
        Response response;
        clock_t start_time;
        std::string savedReqPath;
        std::string savedFile;
        int savedServerID;
        std::string savedMethod;
        std::string savedPostFile;
        Location savedLocation;
        std::string savedFileDel;
        clock_t StartTimeCGI;
        std::string QueryString;
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
        std::string getPath();
        std::string getPathLoc();
        void setPathLoc(std::string loc);
        void loadingFormation(std::string& line);
        void setBody(std::istringstream& buff);
        Client& operator=(const Client& other);
        std::string getfullRequset() const ;
        void setPath(const std::string& path);
        const std::vector<unsigned char>& getBody() const;
        const std::string& getStringBody() const;
        unsigned long getChunkSizee() const;
        void setChunkSizee(unsigned long s);
        void setStringBody(char c, std::string str);
        void setResponse(const Response& rep);
        void setServerId(int serverId);
        Response& getResponse();
        void openFile(std::string file);
        infoMap getInfoMap() const;
        FILE * getOutFile();
        std::string getFilePath();
        bool getDetectCgi();
        void setDetectCgi(bool b);
        bool getOutFileOpened() const;
        void setOutFileOpened(bool b);
        bool getEnteredfirstTime() const;
        void setEnteredfirstTime(bool b);
        size_t getSizeBody() const;
        size_t getSizeAppended() const;
        void setSizeAppended(char c, size_t s);
        std::string trim(std::string& word);
        void ParsingRequest();
        void setTimeOut(clock_t start_time);
        clock_t getTimeOut();
        bool getMatchedTime();
        void setMatchedTime(bool b);
        int getIncremetedFileName();
        void IncremetedFileName();
        int getInd();
        int getPidChild();
        int getStatusChild();
        void setPidChild(int i);
        void setStatusChild(int i);
        void setInd(int ind);
        void setSavedReqPath(std::string str);
        void setSavedFile(std::string str);
        void setSavedServerID(int i);
        void setSavedMethod(std::string str);
        void setSavedPostFIle(std::string str);
        std::string getSavedReqPath();
        std::string getSavedFile();
        int getSavedServerID();
        std::string getSavedMethod();
        std::string getSavedPostFIle();
        void setLocation(Location& loc);
        Location& getLocation();
		void setSavedDileDel(std::string str);
        std::string getSavedFileDel();
        void setStartTimeCGI(clock_t start_time);
        clock_t getStartTimeCGI();
        void setPathInfo(std::string str);
        std::string getPathInfo();
        void setPathInfoChecker(bool b);
        bool getPathInfoChecker();
        std::string  getProtocal();
        std::string FullQueryString(std::string& path);
        const std::string& getQueryString() const;
        void setSizeCompared(size_t s);
        size_t getSizeCompared();
        ~Client();
};

#endif
