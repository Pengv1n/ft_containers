//
// Created by aregenia on 20.02.23.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "defs.hpp"
#include <functional>
#include <iostream>
#include "pair.hpp"
#include "set.hpp"

namespace ft {

    template <class key_compare, class value_type>
    struct  pair_key_compare : public key_compare {
        typedef bool        result_type;
        typedef value_type  first_argument_type;
        typedef value_type  second_argument_type;

        pair_key_compare() : key_compare() {
        }

        explicit pair_key_compare(const key_compare &cmp) : key_compare(cmp) {
        }

        bool operator()(
                const value_type &lhs,
                const value_type &rhs
                ) const {
            return key_compare::operator()(lhs.first, rhs.first);
        }
    };

    template <  class Key,
                class T,
                class Compare = std::less<Key>,
                class Allocator = std::allocator<ft::pair<const Key, T> >
    > class map : set <
            ft::pair<Key, T>,
            ft::pair_key_compare<Compare, pair<Key, T> >,
            Allocator,
            ft::pair<int, int> >
    {
    public:
        typedef Key                                 key_type;
        typedef T                                   mapped_type;
        typedef ft::pair<const Key, T>              value_type;
        typedef std::size_t                         size_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef Compare                             key_compare;
        typedef Allocator                           allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef typename Allocator::pointer         pointer;
        typedef typename Allocator::const_pointer   const_pointer;

        typedef pair_key_compare<
            key_compare,
            value_type
        >   value_compare;

        typedef rb_iterator<
            value_type,
            value_compare,
            allocator_type
        >   iterator;

        typedef rb_iterator<
                const value_type,
                value_compare,
                allocator_type
        >   const_iterator;

        typedef rb_reverse_iterator<
                value_type,
                value_compare,
                allocator_type
        >   reverse_iterator;

        typedef rb_reverse_iterator<
                const value_type,
                value_compare,
                allocator_type
        >   const_reverse_iterator;

    private:
        typedef set <
                value_type,
                value_compare,
                allocator_type
        >   base_class;
        typedef typename iterator::rb_node tree_node;
        typedef

    };

}

#endif //FT_CONTAINERS_MAP_HPP
