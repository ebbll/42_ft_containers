/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:00:26 by eunlee            #+#    #+#             */
/*   Updated: 2023/02/04 17:36:23 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>
#include "./algorithm.hpp"
#include "./iterator.hpp"
#include "./random_access_iterator.hpp"
#include "./reverse_iterator.hpp"
#include "./type_traits.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T															value_type;
		typedef Allocator													allocator_type;
		typedef typename allocator_type::template rebind<value_type>::other	type_allocator;

		typedef typename type_allocator::reference							reference;
		typedef typename type_allocator::const_reference					const_reference;
		
		typedef typename type_allocator::pointer							pointer;
		typedef typename type_allocator::const_pointer						const_pointer;

		typedef ft::random_access_iterator<pointer>							iterator;
		typedef ft::random_access_iterator<const_pointer>					const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		
		typedef ptrdiff_t													difference_type;
		typedef size_t														size_type;

		/* Constructor - Default (Empty Container Constructor) */
		explicit vector(const allocator_type& alloc = allocator_type())
		: _begin(0), _end(0), _cap(0), _alloc(alloc) { }

		/* Constructor - Fill */
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc)
		{
			_begin = _alloc.allocate(n);
			_end = _begin;
			_cap = _begin + n;
			for ( ; n > 0; n--, ++_end) {
				_alloc.construct(_end, val);
			}
		}

		/* Constructor - Range */
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		: _alloc(alloc)
		{
			size_type n = ft::distance(first, last);
			_begin = _alloc.allocate(n);
			_end = _begin;
			_cap = _begin + n;
			for (size_type i = n; i > 0; --i, ++_end) {
				_alloc.construct(_end, *first++);
			}
		}

		/* Constructor - Copy */
		vector(const vector& x)
		: _alloc(x._alloc)
		{
			size_type n = x.size();
			_begin = _alloc.allocate(n);
			_end = _begin;
			_cap = _begin + n;
			for (size_type i = 0; i < n; ++i, ++_end) {
				_alloc.construct(_end, x[i]);
			}
		}
		
		/* Destructor */
		~vector(void)
		{
			if (_begin == 0) { return; }
			while (_end-- != _begin) {
				_alloc.destroy(_end);
			}
			_alloc.deallocate(_begin, this->capacity());
		}

		/* Assign Operator */
		vector& operator=(const vector& x)
		{
			if (this != &x) { assign(x._begin, x._end); }
			return *this;
		}

		/* Assign - Range Version */
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			size_type n = ft::distance(first, last);
			if (capacity() < n) { reserve(n); }
			_end = _begin;
			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(_end, *first++);
				_end++;
			}
		}

		/* Assign - Fill Version */
		void assign(size_type n, const value_type& val)
		{
			if (capacity() < n) { reserve(n); }
			_end = _begin;
			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(_end, val);
				_end++;
			}
		}

		allocator_type get_allocator() const { return _alloc; }

		/* Iterators */
		iterator begin(void) { return iterator(_begin); }
		const_iterator begin(void) const { return const_iterator(_begin); }
		iterator end(void) { return iterator(_end); }
		const_iterator end(void) const { return iterator(_end); }
		reverse_iterator rbegin(void) { return reverse_iterator(end()); }
		const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }
		reverse_iterator rend(void) { return reverse_iterator(begin()); }
		const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

		/* Capacity */
		size_type size(void) const { return size_type(end() - begin()); }
		size_type max_size(void) const { return size_type(-1) / sizeof(T); }

		void resize(size_type n, value_type val = value_type())
		{
			if (n < size()) { erase(begin() + n, end()); }
			else { insert(end(), n - size(), val); }
		}

		size_type capacity(void) const { return size_type(const_iterator(_cap) - begin()); }

		bool empty(void) const { return begin() == end(); }

		void reserve(size_type n)
		{
			if (max_size() < n) {
				throw std::length_error("more than max_size");
			}
			if (capacity() < n) {
				const size_type old_size = size();
				pointer _tmp = _alloc.allocate(n);
				std::uninitialized_copy(_begin, _end, _tmp);
				while (_end-- != _begin) {
					_alloc.destroy(_end);
				}
				_alloc.deallocate(_begin, capacity());
				_begin = _tmp;
				_end = _tmp + old_size;
				_cap = _begin + n;
			}
		}

		/* Element Access */
		reference at(size_type _n)
		{
			if (_n >= size()) {
				throw std::out_of_range("index out of range");
			}
			return (*this)[_n];
		}

		const_reference at(size_type _n) const
		{
			if (_n >= size()) {
				throw std::out_of_range("index out of range");
			}
			return (*this)[_n];
		}
		
		reference operator[](size_type _n) { return *(begin() + _n); }
		const_reference operator[](size_type _n) const { return *(begin() + _n); }

		reference front(void) { return *begin(); }
		const_reference front(void) const { return *begin(); }

		reference back(void) { return *(end() - 1); }
		const_reference back(void) const { return *(end() - 1); }

		/* Modifiers */
		void clear(void) { erase(begin(), end()); }

		iterator insert(iterator position, const value_type& val)
		{
			difference_type diff = position - begin();
			if (_cap == _end) {
				size_type n = size() > 0 ? size() * 2 : 1;
				reserve(n);
			}
			pointer ptr = _begin + diff;
			_alloc.construct(_end);
			++_end;
			std::copy_backward(ptr, _end - 1, _end);
			*ptr = val;
			return position;
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			difference_type diff = position - begin();
			while (capacity() <= size() + n) {
				size_type s = capacity() > 0 ? capacity() * 2 : 1;
				reserve(s);
			}
			pointer ptr = _begin + diff;
			for (size_type i = n; i > 0; --i, ++_end) {
				_alloc.construct(_end);
			}
			std::copy_backward(ptr, _end - n, _end);
			for (size_type i = 0; i < n; ++i) {
				ptr[i] = val;
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
		{
			difference_type n = ft::distance(first, last);
			difference_type diff = position - begin();
			while (capacity() <= size() + n) {
				size_type s = capacity() > 0 ? capacity() * 2 : 1;
				reserve(s);
			}
			pointer ptr = _begin + diff;
			for (difference_type i = n; i > 0; --i, ++_end) {
				_alloc.construct(_end);
			}
			std::copy_backward(ptr, _end - n, _end);
			for (InputIterator it = first; it != last; ++it) {
				*ptr = *it;
				++ptr;
			}
		}

		iterator erase(iterator position)
		{
			difference_type diff = position - begin();
			pointer ptr = _begin + diff;
			std::copy(ptr + 1, _end, ptr);
			--_end;
			_alloc.destroy(_end);
			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type n = ft::distance(first, last);
			std::copy(last, end(), first);
			for (difference_type i = 0; i < n; ++i) {
				--_end;
				_alloc.destroy(_end);
			}
			return first;
		}

		void push_back(const value_type& val)
		{
			if (_cap == _end) {
				size_type n = size() > 0 ? size() * 2 : 1;
				reserve(n);
			}
			_alloc.construct(_end, val);
			++_end;
		}

		void pop_back(void)
		{
			--_end;
			_alloc.destroy(_end);
		}

		void swap(vector& x)
		{
			std::swap(_begin, x._begin);
			std::swap(_end, x._end);
			std::swap(_cap, x._cap);
			std::swap(_alloc, x._alloc);
		}

	private:
		pointer			_begin;
		pointer			_end;
		pointer			_cap;
		allocator_type	_alloc;
	};

	/* Relational Operators */
	template <typename T, class Allocator>
	bool operator==(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
	{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

	template <typename T, class Allocator>
	bool operator!=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
	{ return !(x == y); }

	template <typename T, class Allocator>
	bool operator<(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
	{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

	template <typename T, class Allocator>
	bool operator<=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
	{ return !(y < x); }

	template <typename T, class Allocator>
	bool operator>(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
	{ return y < x; }

	template <typename T, class Allocator>
	bool operator>=(const ft::vector<T, Allocator>& x, const ft::vector<T, Allocator>& y)
	{ return !(x < y); }

	template <typename T, class Allocator>
	void swap(ft::vector<T, Allocator>& x, ft::vector<T, Allocator>& y)
	{ x.swap(y); }
}

#endif
