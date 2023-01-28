/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:45:48 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/27 22:50:36 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {
	/* Equal - Equality */
	template <typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	/* Equal - Predicate */
	template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred)
	{
		while (first1 != last1) {
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	/* Lexicographical Compare - Default */
	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) return false;
			else if (*first1 < *first2) return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	/* Lexicographical Compare - Custom */
	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) return false;
			else if (comp(*first1, *first2)) return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}
}

#endif
