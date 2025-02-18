/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:59:02 by ncastell          #+#    #+#             */
/*   Updated: 2025/02/18 23:18:17 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <exception>

class IRCException : public std::exception
{
	protected:
		std::string	message;

	public:
		IRCException(const std::string& msg);
		virtual ~IRCException() throw() {}
		virtual const char* what() const throw();
};

class PortExcept : public IRCException
{
	public:
		PortExcept();
};

class PassExcept : public IRCException
{
	public:
		PassExcept();
};

class SocketExcept : public IRCException
{
	public:
		SocketExcept(const std::string& msg);
};
