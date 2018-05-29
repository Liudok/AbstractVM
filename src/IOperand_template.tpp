
#include "../include/IOperand_template.hpp"
#include "../include/Factory.hpp"
#include <float.h>

template <typename T>
Type_Template<T>::Type_Template() {}

template <typename T>
Type_Template<T>::Type_Template(eOperandType type, std::string value): _type(type), _str(value) {

	this->_precision = find_out_precision(this->_str);
	char *s = (char *)_str.c_str();
	if (s[0] == '+')
		s++;
	std::string str = std::string(s);
	_str = str;
}

template <typename T>
Type_Template<T>::~Type_Template() {}

template <typename T>
Type_Template<T>:: Type_Template(const Type_Template & other)
{
	*this = other;
}

template <typename T>
Type_Template<T>& Type_Template<T>::operator=(Type_Template const &src) {
	if (this != src)
	{
		this->_type = src._type;
		this->_str = src._str;
		this->value = src.value;
		this->_precision = src._precision;
	}
	return (*this);
}

template <typename T>
eOperandType Type_Template<T>::getType() const {
	return (this->_type);
}

template <typename T>
int Type_Template<T>::getPrecision() const {
	return (this->_precision);
}

template <typename T>
int Type_Template<T>::find_out_precision(std::string const str1) const
{
	char c1 = '.';
	char c2 = ',';
	int ret = 0;

	const char *str = str1.c_str();
	while(*str != c1 && *str != c2 && *str)
		str++;
	while(*str != ')' && *str)
	{
		str++;
		ret++;
	}
	if (ret > 0)
		ret--;
	return (ret);
}

template <typename T>
int Type_Template<T>::chech_overflow(eOperandType a, eOperandType b, double n1, double n2) const {
	a = (a > b) ? a : b;
	double max = 127;
	if (n1 >= 0 && n2 >= 0)
	{
		if (a == 0)
		{
			max = max - n1;
			if (n2 > max)
				return (0);
		}
		else if (a == 1)
			max = SHRT_MAX;
		else if (a == 2)
			max = INT_MAX;
		else if (a == 3)
			max = FLT_MAX;
		else if (a == 4)
			max = DBL_MAX;
		max = max - n1;
		if (n2 > max)
			return (0);
	}
	else if (n1 < 0 && n2 < 0)
	{
		max = -127;
		if (a == 0)
		{
			max = max - n1;
			if (n2 < max)
				return (0);
		}
		if (a == 1)
			max = -SHRT_MAX;
		else if (a == 2)
			max = -INT_MAX;
		else if (a == 3)
			max = -FLT_MAX;
		else if (a == 4)
			max = -DBL_MAX;
		max = max - n1;
		if (n2 < max)
			return (0);
	}
	return (1);
}

template <typename T>
IOperand const* Type_Template<T>::operator+(IOperand const &rhs) const {

	Factory factory;
	double sum;
	std::string sum_str;
	int presi;
	eOperandType a;
	eOperandType b;

	sum = std::stod(this->toString());
	double tmp = sum;
	a = this->getType();
	presi = this->getPrecision();

	if (rhs.getPrecision() > presi)
		presi = rhs.getPrecision();
	sum += std::stod(rhs.toString());
	b = rhs.getType();
	IOperand const * new_operand;
	if (!chech_overflow(a, b, tmp, sum))
	{
		throw Avm::avm_exception("ERROR: overflow of type");
	}
	if (a > b)
	{
		sum_str = factory.get_str(a, presi, sum);
		new_operand = factory.createOperand(a, sum_str);
	}
	else
	{
		sum_str = factory.get_str(b, presi, sum);
		new_operand = factory.createOperand(b, sum_str);
	}
	return (new_operand);
}

template <typename T>
IOperand const* Type_Template<T>::operator-(IOperand const &rhs) const {

	Factory factory;
	double sum;
	std::string sum_str;
	int presi;
	eOperandType a;
	eOperandType b;

	sum = std::stod(this->toString());
	a = this->getType();

	presi = this->getPrecision();
	if (rhs.getPrecision() > presi)
		presi = rhs.getPrecision();

	sum -= std::stod(rhs.toString());
	b = rhs.getType();
	IOperand const * new_operand;
	if (a > b)
	{
		sum_str = factory.get_str(a, presi, sum);
		new_operand = factory.createOperand(a, sum_str);
	}
	else
	{
		sum_str = factory.get_str(b, presi, sum);
		new_operand = factory.createOperand(b, sum_str);
	}
	return (new_operand);
}

template <typename T>
IOperand const* Type_Template<T>::operator*(IOperand const &rhs) const {

	Factory factory;
	double sum;
	std::string sum_str;
	int presi;
	eOperandType a;
	eOperandType b;

	sum = std::stod(this->toString());
	a = this->getType();
	presi = this->getPrecision();
	if (rhs.getPrecision() > presi)
		presi = rhs.getPrecision();

	sum *= std::stod(rhs.toString());

	b = rhs.getType();
	IOperand const * new_operand;
	if (a > b)
	{
		sum_str = factory.get_str(a, presi, sum);
		new_operand = factory.createOperand(a, sum_str);
	}
	else
	{
		sum_str = factory.get_str(b, presi, sum);
		new_operand = factory.createOperand(b, sum_str);
	}
//	std::cout << "after = " << new_operand->toString() <<std::endl;
	return (new_operand);
}

template <typename T>
IOperand const* Type_Template<T>::operator/(IOperand const &rhs) const {

	Factory factory;
	double sum;
	std::string sum_str;
	int presi;
	eOperandType a;
	eOperandType b;

	sum = std::stod(this->toString());
	a = this->getType();

	presi = this->getPrecision();
	if (rhs.getPrecision() > presi)
		presi = rhs.getPrecision();

	sum /= std::stod(rhs.toString());
	if (sum == 0 || std::stod(rhs.toString()) == 0)
	{
		throw Avm::avm_exception("ERROR: 0 value detected as a result of division or as second argument (no division by 0 is allowed!)");
	}
	b = rhs.getType();
	IOperand const * new_operand;
	if (a > b)
	{
		sum_str = factory.get_str(a, presi, sum);
		new_operand = factory.createOperand(a, sum_str);
	}
	else
	{
		sum_str = factory.get_str(b, presi, sum);
		new_operand = factory.createOperand(b, sum_str);
	}
	return (new_operand);
}

template <typename T>
IOperand const* Type_Template<T>::operator%(IOperand const &rhs) const {
	if (this->getType() >= Float)
	{
		throw Avm::avm_exception("ERROR: modulo operation is to for floating point types");
	}
	Factory factory;
	int sum;
	std::string sum_str;
	int presi;
	eOperandType a;
	eOperandType b;


	sum = std::stod(this->toString());
	a = this->getType();

	presi = this->getPrecision();
	if (rhs.getPrecision() > presi)
		presi = rhs.getPrecision();
	int sum2 = std::stod(rhs.toString());
	sum = sum % sum2;
	if (sum == 0 || std::stod(rhs.toString()) == 0)
	{
		throw Avm::avm_exception("ERROR: 0 value detected as a result of modulo or as second argument (no division by 0 is allowed!)");
	}
	b = rhs.getType();
	IOperand const * new_operand;
	if (a > b)
	{
		sum_str = factory.get_str(a, presi, sum);
		new_operand = factory.createOperand(a, sum_str);
	}
	else
	{
		sum_str = factory.get_str(b, presi, sum);
		new_operand = factory.createOperand(b, sum_str);
	}
	return (new_operand);
}


template <typename T>
std::string const& Type_Template<T>::toString() const {
	return _str;
}
