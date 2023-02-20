//
// Created by aregenia on 17.02.23.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

    template <  class T,
                class Container = ft::vector<T> >
    class stack {
    public:
        typedef          Container                   container_type;
        typedef typename Container::value_type       value_type;
        typedef typename Container::size_type        size_type;
        typedef typename Container::reference        reference;
        typedef typename Container::const_reference  const_reference;
    private:
        Container   data;
    public:
        explicit stack(const Container &cont = Container()) : data(cont)
        /**
         *  Copy-constructs the underlying container c with the contents of cont
         * @param cont container to be used as source to initialize the underlying container
         */
        {
        }

        stack(const stack &other) : data(other.data) {
        }

        ~stack() {}

        stack   &operator=(const stack &other)
        /**
         * Replaces the contents of the container adaptor with those of other
         * @param other another container adaptor to be used as source
         * @return new object stack
         */
        {
            data = other.data;
            return *this;
        }

        // =================== Element_access ======================================

        reference   top()
        /**
         * Returns reference to the top element in the stack
         * @return reference to the last element
         * time O(1)
         */
        {
            return data.back();
        }

        const_reference top() const
        /**
         * Returns const reference to the top element in the stack
         * @return const reference to the element
         * time O(1)
         */
        {
            return data.back();
        }

        // =================== Capacity ============================================

        bool    empty() const
        /**
         * Checks if the underlying container has no elements
         * @return true if the underlying container is empty, false otherwise
         * time O(1)
         */
        {
            return data.empty();
        }

        size_type   size() const
        /**
         * Returns the number of elements in the underlying container
         * @return The number of elements in the container
         * time O(1)
         */
        {
            return data.size();
        }

        // =================== Modifiers ===========================================

        void    push(const value_type &value)
        /**
         * Pushes the given element value to the top of the stack
         * @param value the value of the element to push
         * time O(1)
         */
        {
            data.push_back(value);
        }

        void    pop()
        /**
         * Removes the top element from the stack
         * time O(1)
         */
        {
            data.pop_back();
        }

        // =================== Lexicographical compare ==========================

        friend bool    operator==(
                const ft::stack<T, Container> &lhs,
                const ft::stack<T, Container> &rhs)
        {
            return lhs.data == rhs.data;
        }

        friend bool    operator!=(
                const ft::stack<T, Container> &lhs,
                const ft::stack<T, Container> &rhs)
        {
            return lhs.data != rhs.data;
        }

        friend bool    operator<(
                const ft::stack<T, Container> &lhs,
                const ft::stack<T, Container> &rhs)
        {
            return lhs.data < rhs.data;
        }

        friend bool    operator<=(
                const ft::stack<T, Container> &lhs,
                const ft::stack<T, Container> &rhs)
        {
            return lhs.data <= rhs.data;
        }

        friend bool    operator>(
                const ft::stack<T, Container> &lhs,
                const ft::stack<T, Container> &rhs)
        {
            return lhs.data > rhs.data;
        }

        friend bool    operator>=(
                const ft::stack<T, Container> &lhs,
                const ft::stack<T, Container> &rhs)
        {
            return lhs.data >= rhs.data;
        }

    };

}

#endif //FT_CONTAINERS_STACK_HPP
