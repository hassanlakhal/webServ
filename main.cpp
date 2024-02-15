/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:20:40 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/15 13:47:09 by eej-jama         ###   ########.fr       */
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
        else if (ac == 1){
            std::string conf_file = "./configfile.yaml";
            std::ifstream cfile;
            cfile.open(conf_file.c_str());
            if(cfile.is_open()){
                cfile.close();
                loadingData(conf_file);
            }
            else{
                cfile.close();
                throw std::runtime_error("Error in opening confique file");
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}
