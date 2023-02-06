/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:32:19 by eunlee            #+#    #+#             */
/*   Updated: 2023/02/03 10:59:40 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "./iterator.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		/* Constructor - Default */
		reverse_iterator(void) { }
		/* Constructor - Initialization */
		explicit reverse_iterator(iterator_type _x) : _current(_x) { }
		reverse_iterator(const reverse_iterator& _x) : _current(_x._current) { }

		/* Constructor - Copy */
		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& _x) : _current(_x.base()) { }

		/* Destructor */
		~reverse_iterator(void) { }

		/* Base */
		iterator_type base(void) const { return _current; }

		/* Assign */
		template <typename U>
		reverse_iterator& operator=(const reverse_iterator<U>& other)
		{
			_current = other.base();
			return *this;
		}

		/* Access the Pointed-To Element */
		reference operator*(void) const { Iterator _tmp = _current; return *--_tmp; }
		pointer operator->(void) const { return &operator*(); }

		/* Accees an Element by Index*/
		reference operator[](difference_type _n) const { return *(*this + _n); }

		/* Increment Iterator Position */
		reverse_iterator& operator++(void) { --_current; return *this; }
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			--_current;
			return temp;
		}

		/* Decrement Iterator Position */
		reverse_iterator& operator--(void) { ++_current; return *this; }
		reverse_iterator operator--(int) 
		{
			reverse_iterator temp = *this;
			++_current;
			return temp;
		}

		/* Returns an Iterator Which is Advanced by n or -n Positions Respectively */
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); }

		/* Advances the Iterator by n or -n Positions Respectively */
		reverse_iterator& operator+=(difference_type n) { _current -= n; return *this; }
		reverse_iterator& operator-=(difference_type n) { _current += n; return *this; }

	// TODO - 이 부분 다시 확인
	private:
		Iterator _current;
	};

	/* Relational Operators*/
	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() == rhs.base(); }
	
	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return !(lhs == rhs); }

	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return rhs.base() < lhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return rhs < lhs; }

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return !(rhs < lhs); }

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return !(lhs < rhs); }

	/* Addition Operator - Advances the Iterator */
	template <typename Iterator>
	reverse_iterator<Iterator> 
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) 
	{ return reverse_iterator<Iterator>(it.base() - n); }

	/* Subtraction Operator - Computes the Distance */
	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return rhs.base() - lhs.base(); }
}

#endif
