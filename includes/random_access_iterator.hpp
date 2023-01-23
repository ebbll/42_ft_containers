/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:13:06 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/23 15:46:18 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
	// This iterator adapter is 'normal' in the sense that it does not
	// change the semantics of any of the operators of its iterator
	// parameter.  Its primary purpose is to convert an iterator that is
	// not a class, e.g. a pointer, into an iterator that is a class.
	// The _Container parameter exists solely so that different containers
	// using this template can instantiate different types, even if the
	// _Iterator parameter is the same.

	/* random_access_iterator */
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

		random_access_iterator(void) : _current(Iterator()) { }
		explicit random_access_iterator(const Iterator& _i) : _current(_i) { }
		template <typename U>
		random_access_iterator(const random_access_iterator<U>& _i) : _current(_i.base()) { }
		~random_access_iterator(void) { }

		template <typename U>
		random_access_iterator& operator=(const random_access_iterator<U>& _i) {
			_current = _i.base();
			return *this;
		}

		/* Forward iterator requirements */
		reference operator*() const { return *_current; }
		pointer operator->() const { return _current; }
		
		random_access_iterator& operator++() { ++_current; return *this; }
		random_access_iterator operator++(int) { return random_access_iterator(_current++); }
		random_access_iterator& operator--() { --_current; return *this; }
		random_access_iterator operator--(int) { return random_access_iterator(_current--); }

		/* Random access iterator requirements */
		reference operator[](const difference_type& _n) const { return _current[_n]; }

		random_access_iterator& operator+=(const difference_type& _n) { _current += _n; return *this; }

		random_access_iterator operator+(const difference_type& _n) const { return random_access_iterator(_current + _n); }

		random_access_iterator& operator-=(const difference_type& _n) { _current -= _n; return *this; }

		random_access_iterator operator-(const difference_type& _n) const { return random_access_iterator(_current - _n); }

		difference_type operator-(const random_access_iterator& _i) const { return _current - _i._current; }

		Iterator base(void) const { return _current; }

	private:
		Iterator _current;
	};

	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
										const random_access_iterator<T>& i)
	{
		return random_access_iterator<T>(i.base() + n);
	}

	template<typename _IteratorL, typename _IteratorR>
	typename random_access_iterator<_IteratorL>::difference_type operator-(const random_access_iterator<_IteratorL>& x,
																		const random_access_iterator<_IteratorR>& y)
	{
		return x.base() - y.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const random_access_iterator<_IteratorL>& _lhs, const random_access_iterator<_IteratorR>& _rhs)
	{
		return _lhs.base() == _rhs.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const random_access_iterator<_IteratorL>& _lhs, const random_access_iterator<_IteratorR>& _rhs)
	{
		return _lhs.base() != _rhs.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool operator<(const random_access_iterator<_IteratorL>& _lhs, const random_access_iterator<_IteratorR>& _rhs)
	{
		return _lhs.base() < _rhs.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool operator>(const random_access_iterator<_IteratorL>& _lhs, const random_access_iterator<_IteratorR>& _rhs)
	{
		return _lhs.base() > _rhs.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool operator<=(const random_access_iterator<_IteratorL>& _lhs, const random_access_iterator<_IteratorR>& _rhs)
	{
		return _lhs.base() <= _rhs.base();
	}

	template<typename _IteratorL, typename _IteratorR>
	bool operator>=(const random_access_iterator<_IteratorL>& _lhs, const random_access_iterator<_IteratorR>& _rhs)
	{
		return _lhs.base() >= _rhs.base();
	}
}

#endif