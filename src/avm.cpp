// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   avm.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/17 17:37:50 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/17 17:37:53 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../include/avm.hpp"
#include "../include/Factory.hpp"
#include <float.h>

Avm::Avm()
{
	_regexps[0] = "^[ X|\\tX]*;{1}[^;]";
	_regexps[1] = "^[ X|\\tX]*push[ X|\\tX]*((int8\\()[-,+]?[0-9]*\\)|(int16\\()[-,+]?[0-9]*\\)|(int32\\()[-,+]?[0-9]*\\)|(float\\()[-,+]?[0-9]*.{0,1}[0-9]*\\)|(double\\()[-,+]?[0-9]*.{0,1}[0-9]*\\))[ X|\\tX]*$";
	_regexps[2] = "^[ X|\\tX]*pop[ X|\\tX]*$";
	_regexps[3] = "^[ X|\\tX]*dump[ X|\\tX]*$";
	_regexps[4] = "^[ X|\\tX]*add[ X|\\tX]*$";
	_regexps[5] = "^[ X|\\tX]*sub[ X|\\tX]*$";
	_regexps[6] = "^[ X|\\tX]*mul[ X|\\tX]*$";
	_regexps[7] = "^[ X|\\tX]*div[ X|\\tX]*$";
	_regexps[8] = "^[ X|\\tX]*mod[ X|\\tX]*$";
	_regexps[9] = "^[ X|\\tX]*print[ X|\\tX]*$";
	_regexps[10] = "^[ X|\\tX]*exit[ X|\\tX]*$";
	_regexps[11] = "^[ X|\\tX]*assert[ X|\\tX]*((int8\\()[-,+]?[0-9]*\\)|(int16\\()[-,+]?[0-9]*\\)|(int32\\()[-,+]?[0-9]*\\)|(float\\()[-,+]?[0-9]*.{0,1}[0-9]*\\)|(double\\()[-,+]?[0-9]*.{0,1}[0-9]*\\))[ X|\\tX]*$";
	_regexps[12] = "^[ X|\\tX]*;;[ X|\\tX]*$";
	_valid = 0;
}

Avm::Avm(Avm const &other) {
	*this = other;
}

Avm::~Avm() {}

Avm & Avm::operator=(Avm const &src) {
	if (this != &src) {
		this->_stack = src._stack;
	}
	return (*this);
}

void Avm::read_input(void)
{
	_running = 0;
	std::string line = "";

	while (_running == 0 && std::getline(std::cin, line))
	{
		if (std::regex_match(line, std::regex(_regexps[12])) || std::regex_match(line, std::regex(_regexps[10])))
		{
			_running = 1;
			break;
		}
		else
		{
			try {
				check_validity(&line);
				if (std::regex_match(line, std::regex(_regexps[9])))
					print();
				else if (std::regex_match(line, std::regex(_regexps[1])))
					add_to_stack(line);
				else if (std::regex_match(line, std::regex(_regexps[2])))
					pop();
				else if (std::regex_match(line, std::regex(_regexps[3])))
					dump();
				else if (std::regex_match(line, std::regex(_regexps[4])))
					add();
				else if (std::regex_match(line, std::regex(_regexps[5])))
					sub();
				else if (std::regex_match(line, std::regex(_regexps[6])))
					mul();
				else if (std::regex_match(line, std::regex(_regexps[7])))
					div();
				else if (std::regex_match(line, std::regex(_regexps[8])))
					mod();
				else if (std::regex_match(line, std::regex(_regexps[11])))
				{
					add_to_stack(line);
					assert();
				}
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
				_running = 1;
			}
			if (std::regex_match(line, std::regex(_regexps[12])) || std::regex_match(line, std::regex(_regexps[10])))
			{
				_running = 1;
				break;
			}
			std::cin.clear();
		}
		std::string line = "";
	}

}

void Avm::read_file(std::istream &input, std::string filename) {
	_running = 0;
	std::string line;

	while (_running == 0)
	{
		if (!std::getline(input, line))
			_running = 2;
		if (std::regex_match(line, std::regex(_regexps[12])) || std::regex_match(line, std::regex(_regexps[10])))
		{
			_running = 1;
			break;
		}
		else {
				try {
					check_validity(&line);
					if (std::regex_match(line, std::regex(_regexps[9])))
						print();
					else if (std::regex_match(line, std::regex(_regexps[1])))
						add_to_stack(line);
					else if (std::regex_match(line, std::regex(_regexps[2])))
						pop();
					else if (std::regex_match(line, std::regex(_regexps[3])))
						dump();
					else if (std::regex_match(line, std::regex(_regexps[4])))
						add();
					else if (std::regex_match(line, std::regex(_regexps[5])))
						sub();
					else if (std::regex_match(line, std::regex(_regexps[6])))
						mul();
					else if (std::regex_match(line, std::regex(_regexps[7])))
						div();
					else if (std::regex_match(line, std::regex(_regexps[8])))
						mod();
					else if (std::regex_match(line, std::regex(_regexps[11]))) {
						add_to_stack(line);
						assert();
					}
				}
				catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
		}
		if (!_valid && _running != 0)
		{
			std::cout << "Invalid input. All the mistakes:" << std::endl;
			std::vector<std::string>::iterator it;
			for(it = _errors.begin(); it != _errors.end(); ++it)
				std::cout << *it << std::endl;
		}
	}
	if (_running == 2)
		std::cerr << "File " << filename << ": has no EXIT at the end" << std::endl;
}

std::string Avm::get_rid_of_comments(std::string line)
{
	char c = ';';
	char *str = (char *)line.c_str();
	char *begin = str;
	while(*str != c && *str)
		str++;
	*str = '\0';

	return (std::string(begin, str));
}

void Avm::check_validity(std::string *line)
{
	_valid = 0;

	*line = get_rid_of_comments(*line);

	if ((*line).length() > 0)
	{
		for (int i = 0; i < REGS; ++i)
		{
			if (std::regex_match(*line, std::regex(_regexps[i])))
				_valid = 1;
		}
		if (!_valid)
		{
			_errors.push_back(*line);
			throw Avm::avm_exception("Invalid input: syntax error.");
		}
	}
	else
		_valid = 1;
}

void Avm::add_to_stack(std::string line)
{
	Factory factory;
	eOperandType type;
	IOperand const * new_operand;

	type = factory.find_type(line);
	line = factory.cut_to_value(line);
	new_operand = factory.createOperand(type, line);
	if (!(_running = check_type_match(new_operand)))
		this->_stack.push(new_operand);
}

int Avm::check_type_match(IOperand const *new_operand)
{
	if (new_operand->toString().length() < 10)
	{
		int val = std::stoi(new_operand->toString());
		if (val <= SCHAR_MAX && val >= SCHAR_MIN && (new_operand->getType() == 0))
			return (0);
		else if (val <= SHRT_MAX && val >= SHRT_MIN && (new_operand->getType() == 1))
			return (0);
		else if (val <= INT_MAX && val >= INT_MIN && (new_operand->getType() == 2))
			return (0);
		else if ((new_operand->getType() == 3) && std::stod(new_operand->toString()) <= FLT_MAX && std::stod(new_operand->toString()) >= -FLT_MAX)
			return (0);
		else if ((new_operand->getType() == 4) && std::stod(new_operand->toString()) <= DBL_MAX && std::stod(new_operand->toString()) >= -DBL_MIN)
			return (0);
	}
	else if (new_operand->getType() == 3 || new_operand->getType() == 4)
	{
		char *str = (char*)(new_operand->toString()).c_str();
		short i;
		i = 0;
		while(*str != '.' && *str != ',' && *str)
		{
			str++;
			i++;
			if ((i > 36 && (new_operand->getType() == 3)) || (i > 305 && (new_operand->getType() == 4)))
				throw Avm::avm_exception("ERROR:  the value doesn't match type.");
		}
		if ((new_operand->getType() == 3) && std::stod(new_operand->toString()) <= FLT_MAX && std::stod(new_operand->toString()) >= -FLT_MAX)
			return (0);
		else if ((new_operand->getType() == 4) && std::stod(new_operand->toString()) <= DBL_MAX && std::stod(new_operand->toString()) >= -DBL_MIN)
			return (0);
	}
	throw Avm::avm_exception("ERROR:  the value doesn't match type.");
}

void Avm::print()
{
	if (_stack.size() < 1)
		throw Avm::avm_exception("ERROR: not enough members in stack to print");
	std::deque<IOperand const *>::iterator it;
	char c;
	for (it = _stack.begin(); it != _stack.end() ; ++it)
	{
		;
	}
	--it;
	if ((*it)->getType() == 0)
	{
		c = std::stoi((*it)->toString());
		std::cout << c << std::endl;
	}
	else
		throw Avm::avm_exception("ERROR:  the value at the top of the stack is NOT an 8-bit integer");
}

void Avm::dump() {
	std::deque<IOperand const *>::reverse_iterator it;
	for (it = _stack.rbegin(); it != _stack.rend() ; ++it)
	{
		std::cout << (*it)->toString() << std::endl;
	}
}

void Avm::pop() {
	if (_stack.size() == 0)
	{
		throw Avm::avm_exception("ERROR: stack is empty");
	}
	_stack.pop();
}

void Avm::add() {

	if (_stack.size() < 2)
		throw Avm::avm_exception("ERROR: not enough members in stack to add");
	else
	{
		std::deque<IOperand const *>::reverse_iterator it;
		it = _stack.rbegin();
		IOperand const *m1 = (*it);
		++it;
		IOperand const *m2 = (*it);
		IOperand const * new_operand =  *m2 + *m1;

		if ((_running = check_type_match(new_operand)))
			throw Avm::avm_exception("ERROR: sum doesn't fit max type of two operands");
		else
		{
			_stack.pop();
			_stack.pop();
			_stack.push(new_operand);
		}
	}
}

void Avm::sub() {
	if (_stack.size() < 2)
		throw Avm::avm_exception("ERROR: not enough members in stack to make sub");
	else
	{
		std::deque<IOperand const *>::reverse_iterator it;
		it = _stack.rbegin();

		IOperand const *m1 = (*it);
		++it;
		IOperand const *m2 = (*it);
		IOperand const * new_operand =  *m1 - *m2;
		if ((_running = check_type_match(new_operand)))
			throw Avm::avm_exception("ERROR: result of operation doesn't fit max type of two operands");
		else
		{
			_stack.pop();
			_stack.pop();
			_stack.push(new_operand);
		}
	}
}

void Avm::mul() {

	if (_stack.size() < 2)
		throw Avm::avm_exception("ERROR: not enough members in stack to make mul");
	else
	{
		std::deque<IOperand const *>::reverse_iterator it;
		it = _stack.rbegin();

		IOperand const *m1 = (*it);
		++it;
		IOperand const *m2 = (*it);
		IOperand const * new_operand =  *m1 * *m2;
		if ((_running = check_type_match(new_operand)))
			throw Avm::avm_exception("ERROR: result of operation doesn't fit max type of two operands");
		else
		{
			_stack.pop();
			_stack.pop();
			_stack.push(new_operand);
		}
	}
}

void Avm::div() {
	if (_stack.size() < 2)
		throw Avm::avm_exception("ERROR: not enough members in stack to make division");
	else
	{
		std::deque<IOperand const *>::reverse_iterator it;
		it = _stack.rbegin();

		IOperand const *m1 = (*it);
		++it;
		IOperand const *m2 = (*it);
		IOperand const * new_operand =  *m1 / *m2;
		if ((_running = check_type_match(new_operand)))
			throw Avm::avm_exception("ERROR: result of operation doesn't fit max type of two operands");
		else
		{
			_stack.pop();
			_stack.pop();
			_stack.push(new_operand);
		}
	}
}

void Avm::mod() {
	if (_stack.size() < 2)
		throw Avm::avm_exception("ERROR: not enough members in stack to find modulo");
	else
	{
		std::deque<IOperand const *>::reverse_iterator it;
		it = _stack.rbegin();

		IOperand const *m1 = (*it);
		++it;
		IOperand const *m2 = (*it);
		IOperand const * new_operand =  *m1 % *m2;
		if ((_running = check_type_match(new_operand)))
			std::cout << "ERROR: result of operation doesn't fit max type of two operands" << std::endl;
		else
		{
			_stack.pop();
			_stack.pop();
			_stack.push(new_operand);
		}
	}
}

void Avm::assert() {
	if (_stack.size() < 2)
		throw Avm::avm_exception("ERROR: stack is empty");
	else
	{
		std::deque<IOperand const *>::reverse_iterator it;

		it = _stack.rbegin();
		std::string a = (*it)->toString();
		int a_presi = (*it)->getPrecision();
		++it;
		std::string b = (*it)->toString();
		int b_presi = (*it)->getPrecision();
		if (a_presi != b_presi)
		{
			char *str;
			unsigned long len;
			if (a_presi > b_presi)
			{
				len = b.length() + 1;
				str = (char *)a.c_str();
				str += len;
				while (*str)
				{
					if (*str != '0')
						throw Avm::avm_exception("ERROR: values in stack are not equal");
					str++;
				}
			}
			else
			{
				len = a.length() + 1;
				str = (char *)b.c_str();
				str += len;
				while (*str)
				{
					if (*str != '0')
						throw Avm::avm_exception("ERROR: values in stack are not equal");
					str++;
				}
			}
		}
		else
		{
			if (a.compare(b))
				throw Avm::avm_exception("ERROR: values in stack are not equal");
		}
		_stack.pop();
	}
}

/*
 * EXCEPTIONS
 */

Avm::avm_exception::avm_exception(std::string str) : _message(str){

}

Avm::avm_exception::avm_exception(avm_exception const &src) {
	*this = src;
}

Avm::avm_exception::~avm_exception() throw() {

}

Avm::avm_exception & Avm::avm_exception::operator=(avm_exception const &) {
	return (*this);
}

const char* Avm::avm_exception::what() const throw() {
	return (this->_message).c_str();
}
