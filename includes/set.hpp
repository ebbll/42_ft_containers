/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:47:48 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/24 20:11:22 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <functional>
#include <memory>
#include "./reverse_iterator.hpp"
#include "./type_traits.hpp"
#include "./algorithm.hpp"
#include "./rbtree.hpp"
#include "./pair.hpp"

namespace ft {
	template <typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class set
	{
	public:
		typedef	T										key_type;
		typedef T										value_type;
		typedef Compare									key_compare;
		typedef Compare									value_compare;
		typedef Allocator								allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename allocator_type::template rebind<value_type>::other	type_allocator;
		typedef typename type_allocator::pointer		pointer;
		typedef typename type_allocator::const_pointer	const_pointer;
		typedef std::size_t								size_type;
		typedef ptrdiff_t								difference_type;
		typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::const_iterator	iterator;
		typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::const_iterator	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		/* Constructor */
		explicit set(const key_compare& comp = key_compare(), const type_allocator& alloc = type_allocator())
		: _comp(comp), _tree(_comp, alloc)
		{ }

		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const type_allocator& alloc = type_allocator(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		: _comp(comp), _tree(comp, alloc)
		{
			insert(first, last);
		}
		
		set(const set& x)
		: _comp(x._comp), _tree(x._tree)
		{ }

		/* Destructor */
		~set(void) { }

		set& operator=(const set& s)
		{
			if (this != &s) {
				_comp = s._comp;
				_tree = s._tree;
			}
			return *this;
		}

		/* Iterators */
		iterator begin() { return _tree.begin(); }
		const_iterator begin() const { return _tree.begin(); }
		iterator end() { return _tree.end(); }
		const_iterator end() const { return _tree.end(); }
		reverse_iterator rbegin() { return reverse_iterator(_tree.end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.end()); }
		reverse_iterator rend() { return reverse_iterator(_tree.begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_tree.begin()); }

		/* Capacity */
		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }

		/* Modifiers */
		ft::pair<iterator,bool> insert(const value_type& val) { return _tree.insert(val); }
		iterator insert(iterator position, const value_type& val)
		{
			typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::iterator	rb_iter;
			return _tree.insert((rb_iter&)position, val);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) { return _tree.insert(first, last); }

		void erase(iterator position)
		{
			typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::iterator	rb_iter;
			_tree.erase((rb_iter&)position); 
		}
		size_type erase(const value_type& val) { return _tree.erase(val); }
		void erase(iterator first, iterator last)
		{
			typedef typename ft::rbtree<value_type, key_type, value_compare, type_allocator>::iterator	rb_iter;
			_tree.erase((rb_iter&)first, (rb_iter&)last);
		}

		void swap(set& x) { _tree.swap(x._tree); }

		void clear() { _tree.clear(); }

		/* Observers */
		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return _comp; }

		/* Operations */
		iterator find(const value_type& val) const { return _tree.find(val); }
		size_type count(const value_type& val) const { return !(find(val) == end()); }
		iterator lower_bound(const value_type& val) const { return _tree.lower_bound(val); }
		iterator upper_bound(const value_type& val) const { return _tree.upper_bound(val); }
		ft::pair<iterator,iterator> equal_range(const value_type& val) const { return _tree.equal_range(val); }

		/* Allocator */
		type_allocator get_allocator() const { return _tree.get_allocator(); }

	private:
		Compare _comp;
		ft::rbtree<value_type, key_type, value_compare, type_allocator> _tree;
	};

	template < class Key, class Compare, class Alloc >
	bool operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template < class Key, class Compare, class Alloc >
	bool operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template < class Key, class Compare, class Alloc >
	bool operator<(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template < class Key, class Compare, class Alloc >
	bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template < class Key, class Compare, class Alloc >
	bool operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template < class Key, class Compare, class Alloc >
	bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template < class Key, class Compare, class Alloc >
	void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}

#endif