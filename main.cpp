/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:20:40 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/09 15:24:45 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsingFile.hpp"

int main(int ac, char *av[])
{
    if (ac == 2)
    {     
        std::string input(av[1]);
        // webServer a(input);
        loadingData(input);
        // a.loadConfigFile();
        // a.loadLocation();
    }
}