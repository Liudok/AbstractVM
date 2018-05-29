// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/16 10:25:15 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/16 10:25:17 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "include/avm.hpp"
#include <fstream>

int					main(int ac, char **av)
{
	std::ifstream	ifs;
	Avm				avm;

	if (ac < 2)
	{
		avm.read_input();
	}
	else
	{
		for (int i = 1; i < ac; i++)
		{
			std::ifstream file(av[i]);
			if (!file.is_open())
			{
				std::cout << strerror(errno) << std::endl;
				return (1);
			}
			else
			{
				avm.read_file(file, av[i]);
				file.close();
			}
		}
	}
	return (0);
}
