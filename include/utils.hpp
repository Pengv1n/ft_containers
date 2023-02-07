//
// Created by aregenia on 07.02.23.
//

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

namespace ft {

    template<class T>
    const T &min(const T &a, const T &b) { return (b < a) ? b : a; }

    template<class T>
    const T &max(const T &a, const T &b) { return (a < b) ? b : a; }

}

#endif //FT_CONTAINERS_UTILS_HPP
