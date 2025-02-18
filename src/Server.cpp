/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:52:36 by ncastell          #+#    #+#             */
/*   Updated: 2025/02/18 20:28:26 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
#include "Exception.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw IRCException("Expected: ./IRC <port> <password>");
		IRC(std::atoi(av[1]), av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}