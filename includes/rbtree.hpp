/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:55:09 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/23 15:55:53 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

namespace ft {
	/* node */
	template <typename T>
	class node
	{
	public:
		typedef bool	color_type;
		typedef T		value_type;

		node*			_parent;
		node*			_lchild;
		node*			_rchild;
		color_type		_black;
		value_type		_value;
		
		node(void) : _parent(NULL), _lchild(NULL), _rchild(NULL), _black(color_type()), _value(value_type()) { }
		node(const value_type& value) : _parent(NULL), _lchild(NULL), _rchild(NULL), _black(color_type()), _value(value) { }
		node(const node& n) : _parent(n._parent), _lchild(n._lchild), _rchild(n._rchild), _black(n._black), _value(n._value) { }
		~node(void) { }

		node& operator=(const node& n)
		{
			if (this != &n)
			{
				_parent = n._parent;
				_rchild = n._rchild;
				_lchild = n._lchild;
				_black = n._black;
				_value = n._value;
			}
			return *this;
		}
	};

	template <typename NodePtr>
	bool is_lchild(const NodePtr& ptr) { return ptr == ptr->_parent->_lchild; }

	template <typename NodePtr>
	bool is_rchild(const NodePtr& ptr) { return ptr == ptr->_parent->_rchild; }

	template <typename NodePtr>
	NodePtr get_min_node(NodePtr ptr, NodePtr nil)
	{
		while (ptr->_lchild != nil) {
			ptr = ptr->_lchild;
		}
		return ptr;
	}

	template <typename NodePtr>
	NodePtr get_max_node(NodePtr ptr, NodePtr nil)
	{
		while (ptr->_rchild != nil) {
			ptr = ptr->_rchild;
		}
		return ptr;
	}

	template <typename NodePtr>
	NodePtr get_next_node(NodePtr ptr, NodePtr nil)
	{
		if (ptr->_rchild != nil)
			return get_min_node(ptr->_rchild, nil);
		while (!is_lchild(ptr)) {
			ptr = ptr->_parent;
		}
		return ptr->_parent;
	}

	template <typename NodePtr>
	NodePtr get_prev_node(NodePtr ptr, NodePtr nil)
	{
		if (ptr->_lchild != nil)
			return get_max_node(ptr->_lchild, nil);
		while (!is_rchild(ptr)) {
			ptr = ptr->_parent;
		}
		return ptr->_parent;
	}

	template <typename U, typename V, class Comp>
	bool _is_equal(const U& u, const V& v, Comp comp) { return !comp(u, v) && !comp(v, u); }

	/* tree_iterator */
	template <typename U, typename V>
	class tree_iterator
	{
	public:
		typedef U value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef V* iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type			node_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			node_pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			node_reference;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

		tree_iterator(void) : _cur(NULL), _nil(NULL) { }
		tree_iterator(node_pointer cur, node_pointer nil) : _cur(cur), _nil(nil) { }
		tree_iterator(const tree_iterator& i) : _cur(i._cur), _nil(i._nil) { }
		~tree_iterator(void) { }

		tree_iterator& operator=(const tree_iterator& i)
		{
			if (this != &i) {
				_cur = i._cur;
				_nil = i._nil;
			}
			return *this;
		}

		node_pointer base(void) const { return _cur; }
		pointer operator->(void) const { return &_cur->_value; }
		reference operator*(void) const { return _cur->_value; }

		tree_iterator& operator++(void)
		{
			_cur = ft::get_next_node(_cur, _nil);
			return *this;
		}

		tree_iterator& operator--(void)
		{
			_cur = ft::get_prev_node(_cur, _nil);
			return *this;
		}

		tree_iterator operator++(int)
		{
			tree_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		tree_iterator operator--(int)
		{
			tree_iterator tmp(*this);
			--(*this);
			return tmp;
		}
		
		template <typename T>
		bool operator==(const tree_iterator<T, node_type>& i) const { return _cur == i.base(); }

		template <typename T>
		bool operator!=(const tree_iterator<T, node_type>& i) const { return !(*this == i); }

		friend bool operator==(const tree_iterator& x, const tree_iterator& y) {
			return x._cur == y._cur;
		}

		friend bool operator!=(const tree_iterator& x, const tree_iterator& y) {
			return !(x == y);
		}

		operator tree_iterator<const value_type, node_type>(void) const {
			return tree_iterator<const value_type, node_type>(_cur, _nil);
		}

	private:
		node_pointer _cur;
		node_pointer _nil;
	};

	/* red-black tree */
}

#endif