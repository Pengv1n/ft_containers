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

        // =================== Constructor =========================================
        set() : tree(tree_type())
        /**
         * Default constructor. Constructs empty container.
         * time O(1)
         */
        {
        }

        explicit set(const key_compare &comp,
                     const allocator_type &alloc = allocator_type())
                     : tree(comp, alloc)
        /**
         * Default constructor. Constructs empty container.
         * @param comp comparison function object to use for all comparisons of keys
         * @param alloc allocator to use for all memory allocations of this container
         * time O(1)
         */
        {
        }

        template<class InputIt>
        set(InputIt first, InputIt last,
            const cmp_T &comp = cmp_T(),
            const allocator_T &alloc = allocator_type()) :
            tree(comp, alloc)
        /**
         * Range constructor. Constructs the container with the contents of the range [first, last).
         * @tparam InputIt type of iterator
         * @param first, last the range to copy the elements from
         * @param comp comparison function object to use for all comparisons of keys
         * @param alloc allocator to use for all memory allocations of this container
         * time O(n*log(n))
         */
        {
            while (first != last) {
                tree.insert(*first);
                ++first;
            }
        }

        set(const set &other) : tree(other.tree)
        /**
         * Copy constructor. Constructs the container with the copy of the contents of other.
         * @param other another container to be used as source to initialize the elements of the container with
         * time O(other.size())
         */
        {
        }

        // =================== Destructor ==========================================
        ~set()
        /**
         * Destructs the set.
         * time O(size())
         */
        {}

        // =================== Operator Assign =====================================
        set &operator=(const set &other)
        /**
         * Copy assignment operator. Replaces the contents with a copy of the contents of other.
         * @param other another container to use as data source
         * @return *this set
         * time O(size())
         */
        {
            if (this != &other)
                tree.assign(other.tree);
            return *this;
        }

        // =================== get_allocator =======================================
        allocator_type  get_allocator() const
        /**
         * Returns the allocator associated with the container.
         * @return The associated allocator.
         * time O(1)
         */
        {
            return tree.get_alloc();
        }

        // =================== Iterators ===========================================
        iterator    begin()
        /**
         * Returns an iterator to the first element of the set.
         * @return Iterator to the first element.
         * time O(1)
         */
        {
            if (!size())
                return iterator(tree.end(), true);
            return iterator(tree.begin(), false);
        }

        const_iterator  begin() const
        /**
         * Returns an const iterator to the first element of the set.
         * @return const Iterator to the first element.
         * time O(1)
         */
        {
            if (!size())
                return const_iterator(tree.end(), true);
            return const_iterator(tree.begin(), false);
        }

        iterator    end()
        /**
         * Returns an iterator to the element following the last element of the set.
         * @return Iterator to the element following the last element.
         * time O(1)
         */
        {
            return iterator(tree.end(), true);
        }

        const_iterator  end() const
        /**
         * Returns an const iterator to the element following the last element of the set.
         * @return const Iterator to the element following the last element.
         * time O(1)
         */
        {
            return const_iterator(tree.end(), true);
        }

        reverse_iterator    rbegin()
        /**
         * Returns a reverse iterator to the first element of the reversed set.
         * @return Reverse iterator to the first element.
         * time O(1)
         */
        {
            return reverse_iterator(tree.end(), false);
        }

        const_reverse_iterator  rbegin() const
        /**
         * Returns a const reverse iterator to the first element of the reversed set.
         * @return const Reverse iterator to the first element.
         * time O(1)
         */
        {
            return const_reverse_iterator(tree.end(), false);
        }

        reverse_iterator    rend()
        /**
         * Returns a reverse iterator to the element following the last element of the reversed set.
         * @return Reverse iterator to the element following the last element.
         * time O(1)
         */
        {
            return reverse_iterator(tree.begin(), true);
        }

        const_reverse_iterator  rend() const
        /**
         * Returns a const reverse iterator to the element following the last element of the reversed set.
         * @return const Reverse iterator to the element following the last element.
         * time O(1)
         */
        {
            return const_reverse_iterator(tree.begin(), true);
        }

        // =================== Capacity ============================================
        bool    empty() const
        /**
         * Checks if the container has no elements
         * @return true if the container is empty, false otherwise
         * time O(1)
         */
        {
            return tree.size() == 0;
        }

        size_type   size() const
        /**
         * Returns the number of elements in the container
         * @return The number of elements in the container.
         * time O(1)
         */
        {
            return tree.size();
        }

        size_type   max_size() const
        /**
         * Returns the maximum number of elements the container
         * @return Maximum number of elements.
         * time O(1)
         */
        {
            return std::numeric_limits<size_type>::max();
        }

        // =================== Modifiers ===========================================
        void    clear()
        /**
         * Erases all elements from the container.
         * time O(size())
         */
        {
            tree.destroy();
        }

        ft::pair<iterator, bool>   insert(const value_type &value)
        /**
         * Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
         * @param value element value to insert
         * @return Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a bool value set to true if and only if the insertion took place.
         * time O(log(size()))
         */
        {
            size_type prev_size = tree.size();
            iterator ret = iterator(tree.insert(value));
            return ft::pair<iterator, bool>(ret, !(prev_size == tree.size()));
        }

        iterator    insert(iterator pos, const value_type &value)
        /**
         * inserts value in the position as close as possible to the position just prior to pos.
         * @param pos 	iterator to the position before which the new element will be inserted
         * @param value element value to insert
         * @return Returns an iterator to the inserted element, or to the element that prevented the insertion.
         */
        {
            if (not pos.is_end())
                return iterator(tree.insert(pos.get_node(), value), false);
            return iterator(tree.insert(value), false);
        }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        /**
         * Inserts elements from range [first, last).
         * @tparam InputIt type of iterator
         * @param first, last range of elements to insert
         * time O(Amortized constant) | O(log(size()))
         */
        {
            while (first != last) {
                tree.insert(*first);
                ++first;
            }
        }

        iterator    erase(iterator pos)
        /**
         * Removes specified elements from the container.
         * Removes the element at pos
         * @param pos iterator to the element to remove
         * @return Iterator following the last removed element.
         * time O(Amortized constant)
         */
        {
            tree_node *ret = tree.deleteNode(pos.get_node());
            if (ret == tree.end())
                return iterator(ret, true);
            return iterator(ret, false);
        }

        iterator    erase(iterator first, iterator last)
        /**
         * Removes the elements in the range [first, last), which must be a valid range in *this.
         * @param first, last range of elements to remove
         * @return Iterator following the last removed element.
         * time O(log(size()) + distance(first, last))
         */
        {
            while (first != last) {
                tree.deleteNode(*first++);
            }
            return iterator();
        }

        size_type   erase(const key_type &key)
        /**
         * Removes the element (if one exists) with the key equivalent to key.
         * @param key key value of the elements to remove
         * @return Number of elements removed (0 or 1).
         * time O(log(size()) + count(key))
         */
        {
            size_type prev_size = tree.size();
            tree.deleteNode(key);
            return prev_size - tree.size();
        }

        void    swap(set &other)
        /**
         * Exchanges the contents of the container with those of other.
         * @param other container to exchange the contents with
         * time O(1)
         */
        {
            tree.swap(other.tree);
        }

        // =================== Lookup ==============================================
        size_type   count(const_reference key) const
        /**
         * Returns the number of elements with key key. This is either 1 or 0 since this container does not allow duplicates.
         * @param key key value of the elements to count
         * @return Number of elements with key that compares equivalent to key or x, which, for overload (1), is either 1 or 0.
         * time O(log(size()))
         */
        {
            return tree.find(key);
        }

        iterator    find(const key_type &key)
        /**
         * Finds an element with key equivalent to key.
         * @param key key value of the element to search for
         * @return Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
         * time O(log(size()))
         */
        {
            tree_node *ret = tree.searchKey(key);
            if (ret == nullptr)
                return iterator(tree.end(), true);
            return iterator(ret, false);
        }

        const_iterator    find(const key_type &key) const
        /**
         * Finds an element with key equivalent to key.
         * @param key key value of the element to search for
         * @return const Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
         * time O(log(size()))
         */
        {
            tree_node *ret = tree.searchKey(key);
            if (ret == nullptr)
                return const_iterator(tree.end(), true);
            return const_iterator(ret, false);
        }

        ft::pair<iterator, iterator>    equal_range(const key_type &key)
        /**
         * Compares the keys to key.
         * @param key key value to compare the elements to
         * @return std::pair containing a pair of iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key.
         * time O(log(size()))
         */
        {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator>    equal_range(const key_type &key) const
        /**
         * Compares the keys to key.
         * @param key key value to compare the elements to
         * @return std::pair containing a pair of const iterators defining the wanted range: the first pointing to the first element that is not less than key and the second pointing to the first element greater than key.
         * time O(log(size()))
         */
        {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        iterator    lower_bound(const key_type &key)
        /**
         * Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
         * @param key key value to compare the elements to
         * @return Iterator pointing to the first element that is not less than key. If no such element is found, a past-the-end iterator (see end()) is returned.
         * time O(log(size()))
         */
        {
            tree_node *ret = tree.lower_bound(key);
            if (ret == nullptr)
                return iterator(tree.end(), true);
            return iterator(ret, false);
        }

        const_iterator  lower_bound(const key_type &key) const
        /**
         * Returns an const iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
         * @param key key value to compare the elements to
         * @return const Iterator pointing to the first element that is not less than key. If no such element is found, a past-the-end iterator (see end()) is returned.
         * time O(log(size()))
         */
        {
            tree_node *ret = tree.lower_bound(key);
            if (ret == nullptr)
                return const_iterator(tree.end(), true);
            return const_iterator(ret, false);
        }

        iterator    upper_bound(const key_T &key)
        /**
         * Returns an iterator pointing to the first element that is greater than key.
         * @param key key value to compare the elements to
         * @return Iterator pointing to the first element that is greater than key. If no such element is found, past-the-end (see end()) iterator is returned.
         * time O(log(size()))
         */
        {
            tree_node *ret = tree.upper_bound(key);
            if (ret == nullptr)
                return iterator(tree.end(), true);
            return iterator(ret, false);
        }

        const_iterator  upper_bound(const key_T &key) const
        /**
         * Returns an const iterator pointing to the first element that is greater than key.
         * @param key key value to compare the elements to
         * @return const Iterator pointing to the first element that is greater than key. If no such element is found, past-the-end (see end()) iterator is returned.
         * time O(log(size()))
         */
        {
            tree_node *ret = tree.upper_bound(key);
            if (ret == nullptr)
                return const_iterator(tree.end(), true);
            return const_iterator(ret, false);
        }

        // =================== Observers ===========================================
        key_compare key_comp() const
        /**
         * Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
         * @return The key comparison function object.
         * time O(1)
         */
        {
            return tree.get_comp();
        }

        value_compare   value_comp() const
        /**
         * Returns the function object that compares the values. It is the same as key_comp.
         * @return The value comparison function object.
         * time O(1)
         */
        {
            return tree.get_comp();
        }

        template < class Key, class Compare, class Alloc >
        friend bool    operator==( const ft::set<Key, Compare, Alloc> &lhs,
                            const ft::set<Key, Compare, Alloc> &rhs)
        {
            return lhs.tree == rhs.tree;
        }
    };
}

#endif //FT_CONTAINERS_SET_HPP
