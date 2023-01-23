/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:55:09 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/23 18:37:58 by eunlee           ###   ########.fr       */
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
		typedef U			value_type;
		typedef value_type*	pointer;
		typedef value_type&	reference;
		typedef V*			iterator_type;
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
	template <typename T, class Key, class Comp, class Allocator>
	class rbtree {
	public:
		typedef T		value_type;
		typedef Key		key_type;
		typedef Comp	compare_type;

		typedef node<value_type>							node_type;
		typedef node<value_type>*							node_pointer;
		typedef tree_iterator<value_type, node_type>		iterator;
		typedef tree_iterator<const value_type, node_type>	const_iterator;

		typedef Allocator													allocator_type;
		typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
		typedef std::allocator_traits<node_allocator>						node_traits;

		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;

		rbtree(const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type())
		: _comp(comp), _alloc(alloc), _size(size_type())
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, value_type());
			_nil->_black = true;
			_nil->_lchild = NULL;
			_nil->_rchild = NULL;
			_nil->_parent = NULL;
			_end = _construct_node(value_type());
			_end->_black = true;
			_begin = _end;
		}

		rbtree(const rbtree& t)
		: _comp(t._comp), _alloc(t._alloc), _size(size_type())
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, value_type());
			_nil->_black = true;
			_nil->_lchild = NULL;
			_nil->_rchild = NULL;
			_nil->_parent = NULL;
			_end = _construct_node(value_type());
			_end->_black = true;
			_begin = _end;
			insert(t.begin(), t.end());
		}

		~rbtree(void)
		{
			_destruct_node_recursive(_end);
			_destruct_node(_nil);
		}

		rbtree& operator=(const rbtree& t)
		{
			if (this != &t) {
				rbtree tmp(t);
				swap(tmp);
			}
			return *this;
		}

		/* iterator */
		iterator begin(void) { return iterator(_begin, _nil); }
		const_iterator begin(void) const { return const_iterator(_begin, _nil); }
		iterator end(void) { return iterator(_end, _nil); }
		const_iterator end(void) const { return const_iterator(_end, _nil); }
		
		/* capacity */
		size_type size(void) const { return _size; }
		size_type max_size(void) const { return std::min<size_type>(std::numeric_limits<size_type>::max(),
			node_traits::max_size(node_allocator())); }
		bool empty(void) const { return _size == 0; }

		/* modifiers */
		ft::pair<iterator, bool> insert(const value_type& value)
		{
			node_pointer ptr = _search_parent(value);
			if (ptr != _end && _is_equal(ptr->_value, value, _comp)) {
				return ft::make_pair(iterator(ptr, _nil), false);
			}
			return ft::make_pair(iterator(_insert_internal(value, ptr), _nil), true);
		}

		iterator insert(iterator position, const value_type& value)
		{
			node_pointer ptr = _search_parent(value, position.base());
			if (ptr != _end && _is_equal(ptr->_value, value, _comp)) {
				return iterator(ptr, _nil);
			}
			return iterator(_insert_internal(value, ptr), _nil);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; first++) {
				insert(*first);
			}
		}

		iterator erase(iterator position)
		{
			if (_size == 0) {
				return iterator(_nil, _nil);
			}
			iterator tmp(position);
			++tmp;
			if (position == begin()) {
				_begin = tmp.base();
			}
			--_size;
			_remove_internal(position.base());
			_destruct_node(position.base());
			return tmp;
		}

		template <typename U>
		size_type erase(const U& value)
		{
			iterator it(find(value));
			if (it == end()) { return 0; }
			erase(it);
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last) {
				first = erase(first);
			}
		}

		void swap(rbtree& t)
		{
			std::swap(_nil, t._nil);
			std::swap(_begin, t._begin);
			std::swap(_end, t._end);
			std::swap(_comp, t._comp);
			std::swap(_alloc, t._alloc);
			std::swap(_size, t._size);
		}

		void clear(void)
		{
			rbtree tmp(_comp, _alloc);
			swap(tmp);
		}

		iterator find(const key_type& key) { return iterator(_find_internal(key), _nil); }
		const_iterator find(const key_type& key) const { return const_iterator(_find_internal(key), _nil); }
		iterator lower_bound(const key_type& key) { return iterator(_lower_bound_internal(key), _nil); }
		const_iterator lower_bound(const key_type& key) const { return const_iterator(_lower_bound_internal(key), _nil); }
		iterator upper_bound(const key_type& key) { return iterator(_upper_bound_internal(key), _nil); }
		const_iterator upper_bound(const key_type& key) const { return const_iterator(_upper_bound_internal(key), _nil); }
		ft::pair<iterator, iterator> equal_range(const key_type& key) { return _equal_range_internal(key); }
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const { return _equal_range_internal(key); }

		allocator_type get_allocator(void) const { return _alloc; }

	private:
		node_pointer _nil;
		node_pointer _begin;
		node_pointer _end;
		compare_type _comp;
		node_allocator _alloc;
		size_type _size;

		node_pointer _get_root(void) const { return _end->_lchild; }

		void _set_root(const node_pointer ptr)
		{
			ptr->_parent = _end;
			_end->_lchild = ptr;
		}

		node_pointer _construct_node(const value_type& value)
		{
			node_pointer ptr = _alloc.allocate(1);
			_alloc.construct(ptr, value);
			ptr->_parent = _nil;
			ptr->_lchild = _nil;
			ptr->_rchild = _nil;
			ptr->_black = false;
			return ptr;
		}

		void _destruct_node(node_pointer ptr)
		{
			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
		}

		void _destruct_node_recursive(node_pointer ptr)
		{
			if (ptr == _nil) { return; }
			_destruct_node_recursive(ptr->_lchild);
			_destruct_node_recursive(ptr->_rchild);
			_destruct_node(ptr);
		}

		/* insert하려는 위치의 부모를 찾기 */
		node_pointer _search_parent(const value_type& value, node_pointer position = NULL)
		{
			if (position && position != _end) {
				if (_comp(value, position->_value) && position->_lchild == _nil) {
					iterator prev = iterator(position, _nil);
					if (prev == begin() || _comp(*--prev, value)) { return position; }
				} else if (position->_rchild == _nil) {
					iterator next = iterator(position, _nil);
					if (next == end() || _comp(value, *++next)) { return position; }
				}
			}
			node_pointer cur = _get_root();
			node_pointer tmp = _end;
			for ( ; cur != _nil; )
			{
				tmp = cur;
				if (_comp(value, cur->_value)) {
					cur = cur->_lchild;
				} else if (_comp(cur->_value, value)) {
					cur = cur->_rchild;
				} else {
					return cur;
				}
			}
			return tmp;
		}

		node_pointer _insert_internal(const value_type& value, node_pointer parent)
		{
			node_pointer ptr = _construct_node(value);
			if (parent == _end) {
				_set_root(ptr);
			} else if (_comp(value, parent->_value)) {
				parent->_lchild = ptr;
			} else {
				parent->_rchild = ptr;
			}
			ptr->_parent = parent;
			_insert_fixup(ptr);
			if (_begin == _end || _comp(ptr->_value, _begin->_value)) {
				_begin = ptr;
			}
			_size++;
			return ptr;
		}

		void _insert_fixup(node_pointer ptr)
		{
			while (ptr->_parent->_black == false) {
				if (is_lchild(ptr->_parent)) {
					_insert_fixup_left(ptr);
				} else {
					_insert_fixup_right(ptr);
				}
			}
			_get_root()->_black = true;
		}

		void _insert_fixup_left(node_pointer& ptr)
		{
			node_pointer uncle = ptr->_parent->_parent->_rchild;
			if (!uncle->_black) {
				ptr->_parent->_black = true;
				uncle->_black = true;
				ptr->_parent->_parent->_black = false;
				ptr = ptr->_parent->_parent;
			} else {
				if (is_rchild(ptr)) {
					ptr = ptr->_parent;
					_rotate_left(ptr);
				}
				ptr->_parent->_black = true;
				ptr->_parent->_parent->_black = false;
				_rotate_right(ptr->_parent->_parent);
			}
		}

		void _insert_fixup_right(node_pointer& ptr)
		{
			node_pointer uncle = ptr->_parent->_parent->_lchild;
			if (!uncle->_black) {
				ptr->_parent->_black = true;
				uncle->_black = true;
				ptr->_parent->_parent->_black = false;
				ptr = ptr->_parent->_parent;
			} else {
				if (is_lchild(ptr)) {
					ptr = ptr->_parent;
					_rotate_right(ptr);
				}
				ptr->_parent->_black = true;
				ptr->_parent->_parent->_black = false;
				_rotate_left(ptr->_parent->_parent);
			}
		}

		void _rotate_left(node_pointer ptr)
		{
			node_pointer child = ptr->_rchild;
			ptr->_rchild = child->_lchild;
			if (ptr->_rchild != _nil) {
				ptr->_rchild->_parent = ptr;
			}
			node_pointer parent = ptr->_parent;
			child->_parent = parent;
			if (parent == _end) {
				_set_root(child);
			} else if (is_lchild(ptr)) {
				parent->_lchild = child;
			} else {
				parent->_rchild = child;
			}
			child->_lchild = ptr;
			ptr->_parent = child;
		}

		void _rotate_right(node_pointer ptr)
		{
			node_pointer child = ptr->_lchild;
			ptr->_lchild = child->_rchild;
			if (ptr->_lchild != _nil) {
				ptr->_lchild->_parent = ptr;
			}
			node_pointer parent = ptr->_parent;
			child->_parent = parent;
			if (parent == _end) {
				_set_root(child);
			} else if (is_lchild(ptr)) {
				parent->_lchild = child;
			} else {
				parent->_rchild = child;
			}
			child->_rchild = ptr;
			ptr->_parent = child;
		}

		/* 이식 */
		void _transplant(node_pointer u, node_pointer v)
		{
			if (u->_parent == _end) {
				_set_root(v);
			} else if (is_lchild(u)) {
				u->_parent->_lchild = v;
			} else {
				u->_parent->_rchild = v;
			}
			v->_parent = u->_parent;
		}

		void _remove_internal(node_pointer ptr)
		{
			node_pointer tmp;
			node_pointer fix_node = ptr;
			bool original_color = ptr->_black;
			if (ptr->_lchild == _nil) {
				tmp = ptr->_rchild;
				_transplant(ptr, ptr->_rchild);
			} else if (ptr->_rchild == _nil) {
				tmp = ptr->_lchild;
				_transplant(ptr, ptr->_lchild);
			} else {
				fix_node = get_min_node(ptr->_rchild, _nil);
				original_color = fix_node->_black;
				tmp = fix_node->_rchild;
				if (fix_node->_parent == ptr) {
					tmp->_parent = fix_node;
				} else {
					_transplant(fix_node, fix_node->_rchild);
					fix_node->_rchild = ptr->_rchild;
					fix_node->_rchild->_parent = fix_node;
				}
				_transplant(ptr, fix_node);
				fix_node->_lchild = ptr->_lchild;
				fix_node->_lchild->_parent = fix_node;
				fix_node->_black = ptr->_black;
			}
			if (original_color) {
				_remove_fixup(tmp);
			}
		}

		void _remove_fixup(node_pointer ptr)
		{
			while (ptr != _get_root() && ptr->_black)
			{
				if (is_lchild(ptr)) {
					_remove_fixup_left(ptr);
				} else {
					_remove_fixup_right(ptr);
				}
			}
			ptr->_black = true;
		}

		void _remove_fixup_left(node_pointer& ptr)
		{
			node_pointer w = ptr->_parent->_rchild;
			if (!w->_black) { /* case 1 */
				w->_black = true;
				ptr->_parent->_black = false;
				_rotate_left(ptr->_parent);
				w = ptr->_parent->_rchild;
			}
			if (w->_lchild->_black && w->_rchild->_black) { /* case 2 */
				w->_black = false;
				ptr = ptr->_parent;
			} else {
				if (w->_rchild->_black) { /* case 3 */
					w->_lchild->_black = true;
					w->_black = false;
					_rotate_right(w);
					w = ptr->_parent->_rchild;
				} else { /* case 4 */
					w->_black = ptr->_parent->_black;
					ptr->_parent->_black = true;
					w->_rchild->_black = true;
					_rotate_left(ptr->_parent);
					ptr = _get_root();
				}
			}
		}

		void _remove_fixup_right(node_pointer& ptr)
		{
			node_pointer w = ptr->_parent->_lchild;
			if (!w->_black) { /* case 1 */
				w->_black = true;
				ptr->_parent->_black = false;
				_rotate_right(ptr->_parent);
				w = ptr->_parent->_lchild;
			}
			if (w->_rchild->_black && w->_lchild->_black) { /* case 2 */
				w->_black = false;
				ptr = ptr->_parent;
			} else {
				if (w->_lchild->_black) { /* case 3 */
					w->_rchild->_black = true;
					w->_black = false;
					_rotate_left(w);
					w = ptr->_parent->_lchild;
				} else { /* case 4 */
					w->_black = ptr->_parent->_black;
					ptr->_parent->_black = true;
					w->_lchild->_black = true;
					_rotate_right(ptr->_parent);
					ptr = _get_root();
				}
			}
		}

		template <typename U>
		node_pointer _find_internal(const U& value) const
		{
			node_pointer ptr = _get_root();
			while (ptr != _nil)
			{
				if (_comp(value, ptr->_value)) {
					ptr = ptr->_lchild;
				} else if (_comp(ptr->_value, value)) {
					ptr = ptr->_rchild;
				} else {
					return ptr;
				}
			}
			return _end;
		}

		node_pointer _lower_bound_internal(const key_type& key) const
		{
			node_pointer ptr = _get_root();
			node_pointer tmp = _end;
			while (ptr != _nil)
			{
				if (!_comp(ptr->_value, key)) {
					tmp = ptr;
					ptr = ptr->_lchild;
				} else {
					ptr = ptr->_rchild;
				}
			}
			return tmp;
		}

		node_pointer _upper_bound_internal(const key_type& key) const
		{
			node_pointer ptr = _get_root();
			node_pointer tmp = _end;
			while (ptr != _nil)
			{
				if (_comp(key, ptr->_value)) {
					tmp = ptr;
					ptr = ptr->_lchild;
				} else {
					ptr = ptr->_rchild;
				}
			}
			return tmp;
		}

		template <typename U>
		ft::pair<iterator, iterator> _equal_range_internal(const U& key)
		{
			iterator lower = lower_bound(key);
			iterator upper = upper_bound(key);
			return ft::make_pair(lower, upper);
		}

		template <typename U>
		ft::pair<const_iterator, const_iterator> _equal_range_internal(const U& key) const
		{
			const_iterator lower = lower_bound(key);
			const_iterator upper = upper_bound(key);
			return ft::make_pair(lower, upper);
		}
	};
}

#endif