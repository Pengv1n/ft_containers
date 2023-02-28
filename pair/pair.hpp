//
// Created by aregenia on 20.02.23.
//

#ifndef FT_CONTAINERS_PAIR_HPP
#define FT_CONTAINERS_PAIR_HPP

namespace ft {

    template <
            class T1,
            class T2
    > struct pair {
        typedef T1  first_type;
        typedef T2  second_type;

        T1  first;
        T2  second;

        pair() : first(), second()
        {}

        pair(const T1 &x, const T2 &y) : first(x), second(y)
        {}

        template<class U1, class U2>
        explicit pair(const pair<U1, U2> &p) : first(p.first), second(p.second)
        {}

        ~pair() {}

        pair    &operator=(const pair &a)
        {
            first = a.first;
            second = a.second;
            return *this;
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
