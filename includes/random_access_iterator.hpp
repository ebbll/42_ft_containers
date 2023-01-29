/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:13:06 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/29 22:12:37 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
	template <typename Iterator>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, Iterator>
	{
	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

		/* Constructor - Default */
		random_access_iterator(void) : _current(Iterator()) { }
		/* Constructor - Initialization */
		explicit random_access_iterator(const Iterator& _i) : _current(_i) { }

		/* Constructor - Copy */
		template <typename U>
		random_access_iterator(const random_access_iterator<U>& _i) : _current(_i.base()) { }

		/* Destructor */
		~random_access_iterator(void) { }

		/* Assign */
		template <typename U>
		random_access_iterator& operator=(const random_access_iterator<U>& _i)
		{
			_current = _i.base();
			return *this;
		}

		/* Forward Iterator Requirements */
		reference operator*(void) const { return *_current; }
		pointer operator->(void) const { return _current; }
		
		random_access_iterator& operator++(void) { ++_current; return *this; }
		random_access_iterator operator++(int) { return random_access_iterator(_current++); }
		random_access_iterator& operator--(void) { --_current; return *this; }
		random_access_iterator operator--(int) { return random_access_iterator(_current--); }

		/* Random Access Iterator Requirements */
		reference operator[](const difference_type& _n) const { return _current[_n]; }

		random_access_iterator operator+(const difference_type& _n) const { return random_access_iterator(_current + _n); }
		random_access_iterator operator-(const difference_type& _n) const { return random_access_iterator(_current - _n); }
		random_access_iterator& operator+=(const difference_type& _n) { _current += _n; return *this; }
		random_access_iterator& operator-=(const difference_type& _n) { _current -= _n; return *this; }

		difference_type operator-(const random_access_iterator& _i) const { return _current - _i._current; }

		/* Base */
		Iterator base(void) const { return _current; }

	private:
		Iterator _current;
	};

	template <typename T>
	random_access_iterator<T>
	operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& it)
	{ return random_access_iterator<T>(it.base() + n); }

	template <typename Iterator1, typename Iterator2>
	typename random_access_iterator<Iterator1>::difference_type
	operator-(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() - rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator==(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator<(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
	{ return lhs.base() >= rhs.base(); }
}

#endif
