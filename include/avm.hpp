// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   avm.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/16 10:24:57 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/16 10:25:00 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVM_HPP
# define AVM_HPP

#include <iostream>
#include <vector>
#include <regex>

#define REGS 13
#define TYPES 5

enum eOperandType
{
  Int8,
  Int16,
  Int32,
  Float,
  Double
};

#include "IOperand.hpp"
#include "MyStack.hpp"

class Avm
{

	private:
		MyStack<IOperand const *>	_stack;
		int 						_running;
		std::string					_regexps[REGS];
		std::vector<std::string>	_errors;
		int 						_valid;

	public:
		Avm();
		Avm(Avm const & other);
		~Avm();

		Avm					&operator=(Avm const &src);
		void				read_input(void);
		void				read_file(std::istream& input, std::string filename);
		void				check_validity(std::string *line);
		int					check_type_match(IOperand const * new_operand);
		std::string			get_rid_of_comments(std::string line);
		void				add_to_stack(std::string line);
		void				assert(void);
		void                pop(void);
		void				dump(void);
		void				add(void);
		void				sub(void);
		void				mul(void);
		void				div(void);
		void				mod(void);
		void				print(void);

	class avm_exception: public std::exception
	{
	public:
		avm_exception(std::string str);
		avm_exception(avm_exception const &src);
		virtual ~avm_exception() throw ();

		avm_exception &operator=(avm_exception const &);
		virtual const char* what() const throw ();
		std::string _message;
	};
};

#endif