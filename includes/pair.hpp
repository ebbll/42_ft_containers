/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:50:15 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/29 22:11:43 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;
		
		/* Constructor - Default */
		pair(void) : first(first_type()), second(second_type()) { }
		/* Constructor - Copy */
		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) { }
		/* Constructor - Initialization */
		pair(const first_type& a, const second_type& b) : first(a), second(b) { }

		/* Assign */
		pair& operator=(const pair& p)
		{
			if (this != &p) {
				first = p.first;
				second = p.second;
			}
			return *this;
		}
	};

	/* Relational Operators */
	template <typename T1, typename T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <typename T1, typename T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{ return !(lhs == rhs); }

	template <typename T1, typename T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{ return lhs.first < rhs.first || (!(lhs.first > rhs.first) && lhs.second < rhs.second); }

	template <typename T1, typename T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{ return rhs < lhs; }

	template <typename T1, typename T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{ return !(lhs > rhs); }

	template <typename T1, typename T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{ return !(lhs < rhs); }

	/* Construct Pair Object */
	template <typename T1, typename T2>
	ft::pair<T1, T2> make_pair(T1 x, T2 y)
	{ return ft::pair<T1, T2>(x, y); }
}

#endif
