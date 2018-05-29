// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand_template.hpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/17 14:34:13 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/17 14:34:15 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TYPE_TEMPLATE_H
#define TYPE_TEMPLATE_H

#include "avm.hpp"

template <typename T>
class Type_Template : public IOperand
{

private:
	T				_value;
	eOperandType	_type;
	std::string		_str;
	int				_precision;

public:
	Type_Template();
	Type_Template(eOperandType type, std::string value);
	Type_Template(const Type_Template & other);
	Type_Template &operator=(Type_Template const &src);
	~Type_Template();

	eOperandType		getType() const;
	int					getPrecision() const;
	int					find_out_precision(std::string const str1) const;
	int 				chech_overflow(eOperandType a, eOperandType b, double n1, double n2) const;

	IOperand const*		operator+(IOperand const &rhs) const;
	IOperand const*		operator-(IOperand const &rhs) const;
	IOperand const*		operator*(IOperand const &rhs) const;
	IOperand const*		operator/(IOperand const &rhs) const;
	IOperand const*		operator%(IOperand const &rhs) const;
	std::string const & toString( void ) const;
};

#include "../src/IOperand_template.tpp"

#endif
