/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:20:37 by ncastell          #+#    #+#             */
/*   Updated: 2025/02/18 23:47:47 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::IRC(int _port, std::string _password) : port(_port), password(_password)
{
	if (_port < 1024 || _port > 65535) // no sé...
		throw PortExcept();
	if (_password.empty())
		throw PassExcept();
}

IRC::~IRC() { }

int	IRC::getPort() const
{
	return (port);
}
