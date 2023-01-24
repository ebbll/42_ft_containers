/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:43:01 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/24 20:11:59 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "./vector.hpp"

namespace ft {
	template < typename T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

		/* Constructor & Destructor */
		explicit stack(const container_type& container = container_type()) : c(container) { }
		// stack(const stack& s) : c(s.c) { }
		~stack(void) { }

		stack& operator=(const stack& s)
		{
			if (this != &s) {
				c = s.c;
			}
			return *this;
		}

		/* Element Access */
		reference top(void) { return c.back(); }
		const_reference top(void) const { return c.back(); }

		/* Capacity */
		bool empty(void) const { return c.empty(); }
		size_type size(void) const { return c.size(); }

		/* Modifiers */
		void push(const value_type& value) { c.push_back(value); }
		void pop(void) { c.pop_back(); }

		/* Friend Non Member Function for Relational Operators */
		friend bool operator==(const stack& x, const stack& y) { return x.c == y.c; }

		friend bool operator!=(const stack& x, const stack& y) { return x.c != y.c; }

		friend bool operator<(const stack& x, const stack& y) { return x.c < y.c; }

		friend bool operator<=(const stack& x, const stack& y) { return x.c <= y.c; }

		friend bool operator>(const stack& x, const stack& y) { return x.c > y.c; }

		friend bool operator>=(const stack& x, const stack& y) { return x.c >= y.c; }

	protected:
		container_type c;
	};
}

#endif