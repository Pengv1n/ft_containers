//
// Created by aregenia on 20.02.23.
//

#ifndef FT_CONTAINERS_PAIR_HPP
#define FT_CONTAINERS_PAIR_HPP

#include <algorithm>

namespace ft {

    template <
            class T1,
            class T2
    > struct pair {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  first;
        second_type second;

        pair() : first(), second()
        {}

        pair(const first_type &x, const second_type &y) : first(x), second(y)
        {}

        template<class U1, class U2>
        pair(const pair<U1, U2> &p) : first(p.first), second(p.second)
        {}

        ~pair() {}

        pair    &operator=(const pair &a)
        {
            first = a.first;
            second = a.second;
            return *this;
        }

        template<class U1, class U2>
        pair    &operator=(const pair<U1, U2> &other) {
            first = other.first;
            second = other.second;
            return *this;
        }

        void    swap(pair &other) {
            std::swap(first, other.first);
            std::swap(second, other.second);
        }
    };

    template <class T1, class T2>
    ft::pair<T1, T2>    make_pair(T1 t, T2 u)
    {
        return ft::pair<T1, T2>(t, u);
    }

    template <class T1, class T2, class U1, class U2>
    bool    operator==(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }

    template <class T1, class T2, class U1, class U2>
    bool    operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
    {
        return (lhs.first != rhs.first) || (lhs.second != rhs.second);
    }

    template <class T1, class T2, class U1, class U2>
    bool    operator<(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
    {
        return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first < rhs.first;
    }

    template <class T1, class T2, class U1, class U2>
    bool    operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
    {
        return lhs.first == rhs.first ? lhs.second <= rhs.second : lhs.first <= rhs.first;
    }

    template <class T1, class T2, class U1, class U2>
    bool    operator>(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
    {
        return lhs.first == rhs.first ? lhs.second > rhs.second : lhs.first > rhs.first;
    }

    template <class T1, class T2, class U1, class U2>
    bool    operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<U1, U2> &rhs)
    {
        return lhs.first == rhs.first ? lhs.second >= rhs.second : lhs.first >= rhs.first;
    }
}

#endif //FT_CONTAINERS_PAIR_HPP
