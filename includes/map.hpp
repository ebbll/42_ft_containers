/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:38:29 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/25 23:01:57 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include "./reverse_iterator.hpp"
#include "./type_traits.hpp"
#include "./algorithm.hpp"
#include "./pair.hpp"
#include "./rbtree.hpp"

namespace ft {
	template < typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;

		typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef typename allocator_type::template rebind<value_type>::other	type_allocator;

		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename type_allocator::pointer		pointer;
		typedef typename type_allocator::const_pointer	const_pointer;
		
		/* Value Compare */
		class value_compare: public std::binary_function<value_type, value_type, bool>
		{
		friend class ft::map<Key, T, Compare, Allocator>;
		protected:
			key_compare comp;
			value_compare(Compare c) : comp(c) { }
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
			bool operator()(const value_type& x, const key_type& y) const
			{
				return comp(x.first, y);
			}
			bool operator()(const key_type& x, const value_type& y) const
			{
				return comp(x, y.first);
			}
		};

		typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::iterator			iterator;
		typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::const_iterator	const_iterator;
		typedef ft::reverse_iterator<iterator>																reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>														const_reverse_iterator;

		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;

		/* Constructor */
		explicit map(const key_compare& comp = key_compare(), const type_allocator& alloc = type_allocator())
		: _comp(comp), _tree(comp, alloc) { }

		template < class InputIterator >
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const type_allocator& alloc = type_allocator(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		: _comp(comp), _tree(comp, alloc)
		{
			insert(first, last);
		}

		map(const map& x) : _comp(x._comp), _tree(x._tree) { }

		/* Destructor */
		~map(void) { }

		map& operator=(const map& m)
		{
			if (this != &m) {
				_comp = m._comp;
				_tree = m._tree;
			}
			return *this;
		}

		/* Iterators */
		iterator begin() { return _tree.begin(); }
		const_iterator begin() const { return _tree.begin(); }
		iterator end() { return _tree.end(); }
		const_iterator end() const { return _tree.end(); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* Capacity */
		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }

		/* Element access */
		mapped_type& operator[](const key_type& k)
		{
			ft::pair<iterator, bool> p = insert(ft::make_pair(k, mapped_type()));
			return p.first->second;
		}

		/* Modifiers */
		ft::pair<iterator,bool> insert(const value_type& val) { return _tree.insert(val); }
		iterator insert(iterator position, const value_type& val) { return _tree.insert(position, val); }
		template < class InputIterator >
		void insert(InputIterator first, InputIterator last) { return _tree.insert(first, last); }

		void erase(iterator position) { _tree.erase(position); }
		size_type erase(const key_type& k) { return _tree.erase(k); }
		void erase(iterator first, iterator last) { _tree.erase(first, last); }

		void swap(map& x) { _tree.swap(x._tree); }

		void clear() { _tree.clear(); }

		/* Observers */
		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return value_compare(_comp); }

		/* Operations */
		iterator find(const key_type& k) { return _tree.find(k); }
		const_iterator find(const key_type& k) const { _tree.find(k); }
		size_type count(const key_type& k) const { return !(find(k) == end()); }
		iterator lower_bound(const key_type& k) { return _tree.lower_bound(k); }
		const_iterator lower_bound(const key_type& k) const { return _tree.lower_bound(k); }
		iterator upper_bound(const key_type& k) { return _tree.upper_bound(k); }
		const_iterator upper_bound(const key_type& k) const { return _tree.upper_bound(k); }
		ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const { return _tree.equal_range(k); }
		ft::pair<iterator,iterator> equal_range(const key_type& k) { return _tree.equal_range(k); }

		/* Allocator */
		type_allocator get_allocator(void) const { return _tree.get_allocator(); }

	private:
		Compare _comp;
		ft::rbtree<value_type, key_type, value_compare, type_allocator> _tree;
	};

	template < class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}

#endif
