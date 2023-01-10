/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:32:19 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/10 15:35:00 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft {
	/* reverse_iterator */
	template <typename Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename ft::iterator_traits<Iterator>::value_type value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer pointer;
			typedef typename ft::iterator_traits<Iterator>::reference reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

			reverse_iterator(void) { }
			explicit reverse_iterator(iterator_type _x) : _current(_x) { }
			reverse_iterator(const reverse_iterator& _x) : _current(_x._current) { }
			template<typename _Iter>
			reverse_iterator(const reverse_iterator<_Iter>& _x) : _current(_x.base()) { }
			~reverse_iterator(void) {}

			template<typename U>
			reverse_iterator& operator=(const reverse_iterator<U>& other)
			{
				_current = other.base();
				return *this;
			}

			iterator_type base(void) const { return _current; }

			reference operator*() const { Iterator _tmp = _current; return *--_tmp; }
			pointer operator->() const { return &operator*(); }

			reverse_iterator& operator++() { --_current; return *this; }
			reverse_iterator operator++(int)
			{
				reverse_iterator _tmp = *this;
				--_current;
				return _tmp;
			}
			reverse_iterator& operator--() { ++_current; return *this; }
			reverse_iterator operator--(int) 
			{
				reverse_iterator _tmp = *this;
				++_current;
				return _tmp;
			}

			reverse_iterator operator+(difference_type _n) const { return reverse_iterator(_current - _n); }
			reverse_iterator& operator+=(difference_type _n) { _current -= _n; return *this; }
			reverse_iterator operator-(difference_type _n) const { return reverse_iterator(_current + _n); }
			reverse_iterator& operator-=(difference_type _n) { _current += _n; return *this; }

			reference operator[](difference_type _n) const { return *(*this + _n); }

		private:
			Iterator _current;
	};

	template<typename _Iterator1, typename _Iterator2>
	bool operator==(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return _x.base() == _y.base(); }
	
	template<typename _Iterator1, typename _Iterator2>
	bool operator!=(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return !(_x == _y); }

	template<typename _Iterator1, typename _Iterator2>
	bool operator<(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return _y.base() < _x.base(); }

	template<typename _Iterator1, typename _Iterator2>
	bool operator>(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return _y < _x; }

	template<typename _Iterator1, typename _Iterator2>
	bool operator<=(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return !(_y < _x); }

	template<typename _Iterator1, typename _Iterator2>
	bool operator>=(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return !(_x < _y); }

	template<typename _Iterator1, typename _Iterator2>
	typename reverse_iterator<_Iterator1>::difference_type
	operator-(const reverse_iterator<_Iterator1>& _x, 
		const reverse_iterator<_Iterator2>& _y) 
	{ return _y.base() - _x.base(); }


	template<typename _Iterator>
	reverse_iterator<_Iterator> 
	operator+(typename reverse_iterator<_Iterator>::difference_type _n,
		const reverse_iterator<_Iterator>& _x) 
	{ return reverse_iterator<_Iterator>(_x.base() - _n); }
}

#endif