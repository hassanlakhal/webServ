/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:53:53 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/17 10:19:05 by hlakhal-         ###   ########.fr       */
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
