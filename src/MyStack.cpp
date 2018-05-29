// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MyStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/05/16 10:40:49 by lberezyn          #+#    #+#             //
//   Updated: 2018/05/16 10:40:52 by lberezyn         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../include/MyStack.hpp"

template <typename T>
MyStack<T>::MyStack() {}

template <typename T>
MyStack<T>::MyStack(MyStack<T> const &other) {
	*this = other;
}

template <typename T>
MyStack<T>::~MyStack() {}

template <typename T>
MyStack<T> & MyStack<T>::operator=(MyStack<T> const &src) {

	if (this != &src)
	{
		std::deque<IOperand *>::iterator it;
			this->push(*it);
	}
	return (*this);
}

template <typename T>
typename std::deque<T>::iterator	MyStack<T>::begin() {
	return MyStack<T>::c.begin();
}

template <typename T>
typename std::deque<T>::iterator	MyStack<T>::end() {
	return MyStack<T>::c.end();
}

template <typename T>
typename std::deque<T>::reverse_iterator	MyStack<T>::rbegin() {
	return MyStack<T>::c.rbegin();
}

template <typename T>
typename std::deque<T>::reverse_iterator	MyStack<T>::rend() {
	return MyStack<T>::c.rend();
}
