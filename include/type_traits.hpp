//
// Created by aregenia on 05.02.23.
//

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

#include "defs.hpp"

namespace ft {
    // ----------------------------- integral constant -----------------------------
    template<class type_T, type_T type_value>
    struct integral_constant
    {
        const static type_T value = type_value;
    };

    typedef integral_constant<bool, true>   true_type;
    typedef integral_constant<bool, false>  false_type;
    // -------------------------------- is_integral --------------------------------
    template <class type_T> struct is_integral : public false_type {};

    template <> struct is_integral<bool>                : public true_type {};
    template <> struct is_integral<char>                : public true_type {};
    template <> struct is_integral<signed char>         : public true_type {};
    template <> struct is_integral<unsigned char>       : public true_type {};
#if CPP11
    template <> struct is_integral<char16_t>            : public true_type {};
    template <> struct is_integral<char32_t>            : public true_type {};
#endif
#ifdef __WCHAR_TYPE__
    template <> struct is_integral<wchar_t>             : public true_type {};
#endif
    template <> struct is_integral<short>               : public true_type {};
    template <> struct is_integral<unsigned short >     : public true_type {};
    template <> struct is_integral<int>                 : public true_type {};
    template <> struct is_integral<unsigned int>        : public true_type {};
    template <> struct is_integral<long>                : public true_type {};
    template <> struct is_integral<unsigned long>       : public true_type {};
    template <> struct is_integral<long long>           : public true_type {};
    template <> struct is_integral<unsigned long long>  : public true_type {};

#if CPP20
    template <> struct is_integral<char8_t>             : public true_type {};
#endif
    // --------------------------------- enable_if ---------------------------------
    template<bool term, class type_T = void>
    struct enable_if {
    };

    template<class type_T>
    struct enable_if<true, type_T> {
        typedef type_T type;
    };
    // --------------------------------- is_same -----------------------------------
    template <class type_t, class type_Y> struct is_same : public false_type {};
    template <class type_t> struct is_same<type_t, type_t> : public true_type {};
    // --------------------------------- is_iterator -------------------------------
    template <typename type_t, typename = void>
    struct _is_iterator_base : public false_type {};

    template <typename type_t>
    struct _is_iterator_base<
            type_t,
            typename enable_if<!is_same<typename type_t::value_type, void>::value>::type
    > : public true_type {};

    template <typename type_t>
    struct is_iterator : public ft::_is_iterator_base<type_t> {};
    // --------------------------------- remove_const ------------------------------
    template <class type_t>
    struct remove_const {
        typedef type_t type;
    };

    template <class type_t>
    struct remove_const<const type_t>
    {
        typedef type_t type;
    };
}
#endif //FT_CONTAINERS_TYPE_TRAITS_HPP
