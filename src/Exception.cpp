/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:01:43 by ncastell          #+#    #+#             */
/*   Updated: 2025/02/18 20:04:10 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Exception.hpp"

// Constructor base
IRCException::IRCException(const std::string& msg) : message(msg) {}

// Método what()
const char* IRCException::what() const throw() {
    return message.c_str();
}

// Excepción de puerto inválido
PortExcept::PortExcept() : IRCException("Error: Puerto inválido. Debe estar entre 1024 y 65535.") {}

// Excepción de contraseña vacía
PassExcept::PassExcept() : IRCException("Error: La contraseña no puede estar vacía.") {}

// Excepción de error de socket
SocketExcept::SocketExcept(const std::string& msg) : IRCException("Error de socket: " + msg) {}