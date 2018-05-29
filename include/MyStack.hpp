// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MyStack.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/16 10:41:02 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/16 10:41:03 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MYSTACK_HPP
# define MYSTACK_HPP

#include "avm.hpp"
#include <stack>
#include <deque>


template <typename T>
class MyStack : public std::stack<T>
{
	public:
		MyStack();
		MyStack(MyStack const & other);
		~MyStack();
		MyStack<T> &operator=(MyStack<T> const &src);

		typename std::deque<T>::iterator begin();
		typename std::deque<T>::iterator end();
		typename std::deque<T>::reverse_iterator rbegin();
		typename std::deque<T>::reverse_iterator rend();
};

#include "../src/MyStack.cpp"

#endif