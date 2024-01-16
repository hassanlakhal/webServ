/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupServer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:15 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/01/16 16:10:46 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUPSERVER_HPP
#define SETUPSERVER_HPP
#include"webServer.hpp"
#include"Client.hpp"
#include <iostream> 
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <algorithm>

void setupServer(webServer& data);

#endif