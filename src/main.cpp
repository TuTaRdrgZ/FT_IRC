/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:10:50 by droied            #+#    #+#             */
/*   Updated: 2025/02/18 23:28:54 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw IRCException("Expected: ./IRC <port> <password>");
		IRC myServer = IRC(std::atoi(av[1]), av[2]);
		std::cout << "Port: " << myServer.getPort() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
