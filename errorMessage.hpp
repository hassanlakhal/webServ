/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <hlakhal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:27:57 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/19 15:35:52 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include <sstream>

class errorMessage : public std::exception 
{
    public:
        errorMessage();
        errorMessage(int lineNumber, const std::string& message) throw(); 
        virtual const char* what() const throw();
        virtual ~errorMessage() throw() ;
    private:
        std::string message;
};