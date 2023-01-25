/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:50:15 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/25 23:02:11 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
	template < typename T1, typename T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type		first;
		second_type		second;
		
		/* Constructor */
		pair() : first(first_type()), second(second_type()) { }
		pair(const T1& x, const T2& y) : first(x), second(y) { }
		template < class U, class V >
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) { }

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
	template < typename T1, typename T2 >
	bool operator==(const ft::pair<T1, T2> &a, const ft::pair<T1, T2> &b)
	{
		return a.first == b.first && a.second == b.second;
	}

	template < typename T1, typename T2 >
	bool operator!=(const ft::pair<T1, T2> &a, const ft::pair<T1, T2> &b)
	{
		return !(a == b);
	}

	template < typename T1, typename T2 >
	bool operator<(const ft::pair<T1, T2> &a, const ft::pair<T1, T2> &b)
	{
		return a.first < b.first || (!(a.first > b.first) && a.second < b.second); 
	}

	template < typename T1, typename T2 >
	bool operator>(const ft::pair<T1, T2> &a, const ft::pair<T1, T2> &b)
	{
		return b < a;
	}

	template < typename T1, typename T2 >
	bool operator<=(const ft::pair<T1, T2> &a, const ft::pair<T1, T2> &b)
	{
		return !(a > b);
	}

	template < typename T1, typename T2 >
	bool operator>=(const ft::pair<T1, T2> &a, const ft::pair<T1, T2> &b)
	{
		return !(a < b);
	}

	/* Make Pair */
	template < typename T1, typename T2 >
	ft::pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return ft::pair<T1, T2>(t, u);
	}
}

#endif
