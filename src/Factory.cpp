// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Factory.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/16 14:49:43 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/16 14:49:45 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../include/Factory.hpp"
#include "../include/IOperand_template.hpp"
#include <float.h>
#include <cstdint>

Factory::Factory(void) {
	_types[0] = "^[ X|\\tX]*push[ X|\\tX]*((int8\\()[-,+]?[0-9]*\\))[ X|\\tX]*$";
	_types[1] = "^[ X|\\tX]*push[ X|\\tX]*((int16\\()[-,+]?[0-9]*\\))[ X|\\tX]*$";
	_types[2] = "^[ X|\\tX]*push[ X|\\tX]*((int32\\()[-,+]?[0-9]*\\))[ X|\\tX]*$";
	_types[3] = "^[ X|\\tX]*push[ X|\\tX]*((float\\()[-,+]?[0-9]*.{0,1}[0-9]*\\))[ X|\\tX]*$";
	_types[4] = "^[ X|\\tX]*push[ X|\\tX]*((double\\()[-,+]?[0-9]*.{0,1}[0-9]*\\))[ X|\\tX]*$";

}
Factory::Factory(Factory const &other) { *this = other; }
Factory::~Factory(void) {}

Factory &Factory::operator=(Factory const &src) {
	if (this != &src)
	{
		for(int i = 0; i < TYPES; i++)
			_types[i] = src._types[i];
	}

	return (*this);
}

IOperand const * Factory::_createInt8( std::string const & value ) const {
	return new Type_Template<int8_t>(Int8, value);
}

IOperand const * Factory::_createInt16( std::string const & value ) const {
	long ret = std::stod(value);
	if (ret > SHRT_MAX || ret < -SHRT_MAX)
	{
		throw Avm::avm_exception("ERROR: short type overflow");
	}
	return new Type_Template<int16_t>(Int16, value);
}

IOperand const * Factory::_createInt32( std::string const & value ) const {
	long long ret = std::stod(value);
	if (ret > INT_MAX || ret < -INT_MAX)
	{
		throw Avm::avm_exception("ERROR: int type overflow");
	}
	return new Type_Template<int32_t>(Int32, value);
}

IOperand const * Factory::_createFloat( std::string const & value ) const {
	float ret = std::stod(value);
	if (ret > FLT_MAX || ret < -FLT_MAX)
	{
		throw Avm::avm_exception("ERROR: float type overflow");
	}
	return new Type_Template<float>(Float, value);
}

IOperand const * Factory::_createDouble( std::string const & value ) const {
	double ret = std::stod(value);
	if (ret > DBL_MAX || ret < -DBL_MAX)
	{
		throw Avm::avm_exception("ERROR: double type overflow");
	}
	return (new Type_Template<double>(Double, value));
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
	IOperand const *(Factory::*handler[5])(std::string const &) const = {
				&Factory::_createInt8,
				&Factory::_createInt16,
				&Factory::_createInt32,
				&Factory::_createFloat,
				&Factory::_createDouble
	};

	return (this->*(handler[type]))(value);
}

eOperandType Factory::find_type(std::string line) {
	for (int i = 0; i < TYPES; ++i) {
		if (std::regex_match(line, std::regex(_types[i])))
		{
			return ((eOperandType)i);
		}
	}
	return ((eOperandType)0);
}

std::string Factory::cut_to_value(std::string line) {
	char c = '(';
	const char *str = line.c_str();
	while(*str != c && *str)
		str++;
	str++;
	const char *begin = str;
	c = ')';
	while(*str != c && *str)
		str++;
	return (std::string(begin, str));
}


std::string Factory::get_str(eOperandType type, int presi, double sum) {

	if (type == Int8)
	{
		char ret = (char)sum;
		return (std::to_string(ret));
	}
	else if (type == Int16)
	{
		short ret = (short)sum;
		return (std::to_string(ret));
	}
	else if (type == Int32)
	{
		int ret = (int)sum;
		return (std::to_string(ret));
	}
	else if (type == Float)
	{
		float ret = (float)sum;
		char *str = (char *)(std::to_string(ret)).c_str();
		char *begin = str;
		while (*str != '.' && *str)
			str++;
		presi++;
		while (presi-- && *str)
			str++;
		*str = '\0';

		return ((std::string)begin);
	}
	else if (type == Double)
	{
		double ret = sum;
		char *str = (char *)(std::to_string(ret)).c_str();
		char *begin = str;
		while (*str != '.' && *str)
			str++;
		while (presi-- && *str)
			str++;
		*str = '\0';
		return ((std::string)begin);
	}
	throw Avm::avm_exception("ERROR: type problem");
}
