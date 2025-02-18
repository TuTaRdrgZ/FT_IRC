/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:08:29 by ncastell          #+#    #+#             */
/*   Updated: 2025/02/18 23:25:47 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

#include <iostream>
#include <cstdlib> 

class IRC
{
	private:
		int			port;
		std::string	password;

	public:
		IRC(int _port, std::string _password);
		~IRC();

		int		getPort() const;
};
