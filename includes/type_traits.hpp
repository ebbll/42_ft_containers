/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunlee <eunlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:58:48 by eunlee            #+#    #+#             */
/*   Updated: 2023/01/05 20:01:15 by eunlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstdint>

namespace ft {
	/* enable_if */
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	/* integral_constant */
	template<typename T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	/* remove_cv */
	/* remove const, volatile */
	template<class T> struct remove_cv                   { typedef T type; };
	template<class T> struct remove_cv<const T>          { typedef T type; };
	template<class T> struct remove_cv<volatile T>       { typedef T type; };
	template<class T> struct remove_cv<const volatile T> { typedef T type; };

	/* is_integral_base */
	/*	bool / char / char16_t / char32_t / wchar_t
		short / int / long
		unsigned char / unsigned short
		unsigned int / unsigned long */
	template <typename>
	struct is_integral_base : public false_type {};

	template <>
	struct is_integral_base<bool> : public true_type {};

	template <>
	struct is_integral_base<char> : public true_type {};

	template <>
	struct is_integral_base<char16_t> : public true_type {};

	template <>
	struct is_integral_base<char32_t> : public true_type {};

	template <>
	struct is_integral_base<wchar_t> : public true_type {};
	
	template <>
	struct is_integral_base<short> : public true_type {};
	
	template <>
	struct is_integral_base<int> : public true_type {};
	
	template <>
	struct is_integral_base<long> : public true_type {};

	template <>
	struct is_integral_base<unsigned char> : public true_type {};
	
	template <>
	struct is_integral_base<unsigned short> : public true_type {};
	
	template <>
	struct is_integral_base<unsigned int> : public true_type {};

	template <>
	struct is_integral_base<unsigned long> : public true_type {};

	/* is_integral */
	template <typename T>
	struct is_integral : public is_integral_base<typename remove_cv<T>::type> {};
}

#endif