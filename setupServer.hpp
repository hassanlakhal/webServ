/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupServer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:15 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/15 12:25:25 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUPSERVER_HPP
#define SETUPSERVER_HPP
#include"webServer.hpp"
#include <iostream> 
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void setupServer(webServer& data);

#endif