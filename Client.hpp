/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/19 12:45:13 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

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
        std::string body;
        // short port;
    public:
        Client();
        void setRequset(std::string& buff);
        const std::string& getRequset() const;
        const std::string& getMethod() const;
        void setStartLine(std::istringstream& iss);
        const Client& getClinet() const;
        void loadingFormation(std::string& line);
        void setBody(std::istringstream& buff);
        void ParsingRequest();
        ~Client();
};
