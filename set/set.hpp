//
// Created by aregenia on 01.03.23.
//

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include <functional>
#include "defs.hpp"
#include <iostream>
#include "pair.hpp"
#include "rb_iterator.hpp"
#include "rb_tree.hpp"
#include <limits>

namespace ft {

    template<
            class key_T,
            class cmp_T=std::less<key_T>,
            class allocator_T=std::allocator<key_T>,
            class pair_T=ft::pair<int, int> >
    class set {
    public:
        typedef key_T key_type;
        typedef key_T value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef cmp_T key_compare;
        typedef cmp_T value_compare;
        typedef allocator_T allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef ft::rb_iterator<value_type,
                value_compare,
                allocator_type
        > iterator;

        typedef ft::rb_iterator<const value_type,
                value_compare,
                allocator_type
        > const_iterator;

        typedef ft::rb_reverse_iterator<value_type,
                value_compare,
                allocator_type
        > reverse_iterator;

        typedef ft::rb_reverse_iterator<const value_type,
                value_compare,
                allocator_type
        > const_reverse_iterator;

    protected:
        typedef ft::rb_tree<value_type,
                            value_compare,
                            allocator_type
                            >   tree_type;

        typedef typename iterator::rb_node tree_node;

    private:
        tree_type   tree;
    public:
        set() : tree(tree_type()) {
        }

        explicit set(const key_compare &comp,
                     const allocator_type &alloc = allocator_type())
                     : tree(comp, alloc) {
        }

        template<class InputIt>
        set(InputIt first, InputIt last,
            const cmp_T &comp = cmp_T(),
            const allocator_T &alloc = allocator_type()) :
            tree(comp, alloc) {
            bool tmp;
            while (first != last) {
                tree.insert(*first, tmp);
                ++first;
            }
        }

        set(const set &cmp) : tree(cmp.tree) {
        }

        ~set() {}

        set &operator=(const set &a) {
            if (this != &a)
                tree.assign(a.tree);
            return *this;
        }

        allocator_type  get_allocator() const {
            return tree.get_alloc();
        }

        iterator    begin() {
            return iterator(tree.begin(), false);
        }

        const_iterator  begin() const {
            return const_iterator(tree.begin(), false);
        }

        iterator    end() {
            return iterator(tree.end(), true);
        }

        const_iterator  end() const {
            return const_iterator(tree.end(), true);
        }

        reverse_iterator    rbegin() {
            return reverse_iterator(tree.end(), false);
        }

        const_reverse_iterator  rbegin() const {
            return const_reverse_iterator(tree.end(), false);
        }

        reverse_iterator    rend() {
            return reverse_iterator(tree.begin(), true);
        }

        const_reverse_iterator  rend() const {
            return const_reverse_iterator(tree.begin(), true);
        }

        bool    empty() const {
            return tree.size() == 0;
        }

        size_type   size() const {
            return tree.size();
        }

        size_type   max_size() const {
            return std::numeric_limits<size_type>::max();
        }

        void    clear() {
            tree.destroy();
        }

        iterator    insert(iterator pos, const value_type &value) {
            if (not pos.is_end())
                return iterator(tree.insert(pos.get_node(), value), false);
            return iterator(tree.insert(value), false);
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last) {
            while (first != last) {
                tree.insert(*first);
                ++first;
            }
        }

        ft::pair<iterator, bool>   insert(const value_type &value) {
            size_type prev_size = tree.size();
            iterator ret = iterator(tree.insert(value));
            return ft::pair<iterator, bool>(ret, !(prev_size == tree.size()));
        }

        iterator    erase(iterator pos) {
            tree_node *ret = tree.deleteNode(pos.get_node());
            if (ret == tree.end())
                return iterator(ret, true);
            return iterator(ret, false);
        }

        iterator    erase(iterator first, iterator last) {
            while (first != last) {
                if ((first + 1) == last)
                    return erase(first);
                tree.deleteNode(*first++);
            }
            return iterator();
        }

        size_type   erase(const key_type &key) {
            size_type prev_size = tree.size();
            tree.deleteNode(key);
            return prev_size - tree.size();
        }

        void    swap(set &other) {
            tree.swap(other.tree);
        }

        size_type   count(const_reference val) const {
            return tree.find(val);
        }

        iterator    find(const key_type &key) {
            tree_node *ret = tree.searchKey(key);
            if (ret == nullptr)
                return iterator(tree.end(), true);
            return iterator(ret, false);
        }

        const_iterator    find(const key_type &key) const {
            tree_node *ret = tree.searchKey(key);
            if (ret == nullptr)
                return const_iterator(tree.end(), true);
            return const_iterator(ret, false);
        }

        ft::pair<iterator, iterator>    equal_range(const key_type &key) {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator>    equal_range(const key_type &key) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        iterator    lower_bound(const key_type &key) {
            tree_node *ret = tree.lower_bound(key);
            if (ret == nullptr)
                return iterator(tree.end(), true);
            return iterator(ret, false);
        }

        const_iterator  lower_bound(const key_type &key) const {
            tree_node *ret = tree.lower_bound(key);
            if (ret == nullptr)
                return const_iterator(tree.end(), true);
            return const_iterator(ret, false);
        }

        iterator    upper_bound(const key_T &key) {
            tree_node *ret = tree.upper_bound(key);
            if (ret == nullptr)
                return iterator(tree.end(), true);
            return iterator(ret, false);
        }

        const_iterator  upper_bound(const key_T &key) const {
            tree_node *ret = tree.upper_bound(key);
            if (ret == nullptr)
                return const_iterator(tree.end(), true);
            return const_iterator(ret, false);
        }

        key_compare key_comp() const {
            return tree.get_comp();
        }

        value_compare   value_comp() const {
            return tree.get_comp();
        }


    };

}

#endif //FT_CONTAINERS_SET_HPP
