/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:20:40 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/13 18:14:45 by eej-jama         ###   ########.fr       */
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
            loadingData(input);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}
