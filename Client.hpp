/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/20 15:17:50 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include<vector>

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
        void loadingFormation(std::string& line);
        void setBody(std::istringstream& buff);
        Client& operator=(const Client& other);
        const std::vector<unsigned char>& getBody() const;
        void ParsingRequest();
        ~Client();
};
