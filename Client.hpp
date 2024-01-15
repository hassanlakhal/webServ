/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/15 11:44:52 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<iostream>


class Client
{
private:
    std::string host;
    std::string method;
    // short port;
public:
    Client();
    void ParsingRequest(std::string& );
    ~Client();
};
