// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Factory.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/16 14:49:55 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/16 14:49:56 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "avm.hpp"

class Factory
{
	private:
		IOperand const *  _createInt8( std::string const & value ) const;
		IOperand const *  _createInt16( std::string const & value ) const;
		IOperand const *  _createInt32( std::string const & value ) const;
		IOperand const *  _createFloat( std::string const & value ) const;
		IOperand const *  _createDouble( std::string const & value ) const;
		std::string _types[TYPES];
	public:
		Factory(void);
		Factory(Factory const &other);
		~Factory(void);

		Factory				&operator=(Factory const &src);
		eOperandType		find_type(std::string line);
		std::string			cut_to_value(std::string line);
		std::string			get_str(eOperandType type, int presi, double sum);
		IOperand const		*createOperand( eOperandType type, std::string const & value ) const;
};

#endif