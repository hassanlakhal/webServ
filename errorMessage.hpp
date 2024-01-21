/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/21 22:07:42 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include <sstream>
#include<map>
// #include"Server.hpp"
class errorMessage : public std::exception 
{
    public:
        errorMessage();
        errorMessage(int satus,int ind) throw();
        virtual const char* what() const throw();
        virtual ~errorMessage() throw();
    protected:
        std::string message;
        std::map<int , std::string> error;
};