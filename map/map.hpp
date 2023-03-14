//
// Created by aregenia on 20.02.23.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
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
    > class map : public set <
            ft::pair<const Key, T>,
            ft::pair_key_compare<Compare, ft::pair<const Key, T> >,
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
                allocator_type,
                ft::pair<int, int>
        >   base_class;
        typedef typename iterator::rb_node                  tree_node;
        typedef ft::pair<iterator, bool>                    insert_pair;
        typedef ft::pair<iterator, iterator>                range_pair;
        typedef ft::pair<const_iterator, const_iterator>    const_range_pair;

        mapped_type _dummy_val;
    public:
        map() : base_class()
        {}

        explicit map(const key_compare &comp,
            const allocator_type &alloc=allocator_type()) :
            base_class(value_compare(comp), alloc)
        {}

        template <class InputIt>
        map(
                InputIt first,
                InputIt last,
                const key_compare &comp=key_compare(),
                const allocator_type &alloc=allocator_type()) :
                base_class(first, last, value_compare(comp), alloc)
        {}

        map(const map &cpy) : base_class(cpy)
        {}

        mapped_type &at(const key_type &key) const {
            return _at(key);
        }

        mapped_type &operator[](const key_type &key) {
            return this->tree.insert(
                    value_type(key, mapped_type())
                    )->get_key().second;
        }

        size_type   count(const key_type &key) const {
            return base_class::count(value_type(key, _dummy_val));
        }

        iterator    find(const key_type &key) {
            return base_class::find(value_type(key, _dummy_val));
        }

        range_pair  equal_range(const key_type &key) {
            return range_pair(lower_bound(key), upper_bound(key));
        }

        const_range_pair    equal_range(const key_type &key) const {
            return const_range_pair(lower_bound(key), upper_bound(key));
        }

        iterator lower_bound(const key_type &key)
        {
            return base_class::lower_bound(value_type(key, _dummy_val));
        }

        const_iterator lower_bound(const key_type &key) const
        {
            return base_class::lower_bound(value_type(key, _dummy_val));
        }

        iterator upper_bound(const key_type &key)
        {
            return base_class::upper_bound(value_type(key, _dummy_val));
        }

        const_iterator upper_bound(const key_type &key) const
        {
            return base_class::upper_bound(value_type(key, _dummy_val));
        }

    private:
        mapped_type &_at(const key_type &key) const {
            const_iterator nd =
                    base_class::find(value_type(key, _dummy_val));
            if (nd.is_end())
                throw std::out_of_range("ft::map::at()");
            return nd.get_node()->get_key().second;
        }
    };

}

#endif //FT_CONTAINERS_MAP_HPP
