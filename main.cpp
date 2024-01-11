/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:20:40 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/10 22:49:34 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsingFile.hpp"

int main(int ac, char *av[])
{
    try
    {
        webServer s;
        if (ac == 2)
        {     
            std::string input(av[1]);
            // webServer a(input);
            loadingData(input);
            // webServer a(s);
            // std::cout << s.getServer()[0].getHost() << std::endl;
            // std::cout << s.getServer()[1].getHost() << std::endl;
            // std::cout << s.getServer()[2].getHost() << std::endl;
            // a.loadConfigFile();
            // a.loadLocation();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}