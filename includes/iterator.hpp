/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:18:12 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/23 15:44:20 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {
	struct input_iterator_tag	{ };
	struct output_iterator_tag	{ };
	struct forward_iterator_tag			: public input_iterator_tag			{ };
	struct bidirectional_iterator_tag	: public forward_iterator_tag		{ };
	struct random_access_iterator_tag	: public bidirectional_iterator_tag	{ };

	template<typename Category, typename T, typename Distance = ptrdiff_t,
			typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef ft::random_access_iterator_tag			iterator_category;
		typedef T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef T*										pointer;
		typedef T&										reference;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef ft::random_access_iterator_tag			iterator_category;
		typedef T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef const T*								pointer;
		typedef const T&								reference;
	};

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return (result);
	}
}

#endif