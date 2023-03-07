//
// Created by aregenia on 01.03.23.
//

#ifndef FT_CONTAINERS_RB_ITERATOR_HPP
#define FT_CONTAINERS_RB_ITERATOR_HPP

#include "normal_iterator.hpp"
#include "rb_tree.hpp"

namespace ft {

    template<typename value_t, typename cmp_t, typename alloc_t>
    class rb_iterator_base :
            public ft::iterator<ft::bidirectional_iterator_tag, value_t> {
    private:
        typedef ft::bidirectional_iterator_tag tag;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_t> iterator_traits;

    public:
        typedef typename iterator_traits::iterator_category iterator_category;
        typedef typename iterator_traits::value_type value_type;
        typedef typename iterator_traits::difference_type difference_type;
        typedef typename iterator_traits::pointer pointer;
        typedef typename iterator_traits::reference reference;
        typedef const reference const_reference;
        typedef const pointer const_pointer;

    protected:
        typedef ft::rb_tree<
                typename ft::remove_const<value_type>::type,
                cmp_t,
                alloc_t> tree_type;
        typedef typename tree_type::rb_node rb_node;
    private:
        rb_node *ptr;
        bool _end;

    public:
        reference operator*() const {
            return ptr->get_key();
        }

        bool operator==(const rb_iterator_base &cmp) const {
            bool x = _end;
            bool y = cmp._end;
            bool z = ptr == cmp.ptr;
            return (x and y) or ((not x) and (not y) and z);
        }

        bool operator!=(const rb_iterator_base &cmp) const {
            return not operator==(cmp);
        }

        rb_node *get_node() const {
            return ptr;
        }

        bool is_end() const {
            return _end;
        }

    protected:
        rb_iterator_base() :
                ptr(nullptr),
                _end(false) {}

        rb_iterator_base(rb_node *ptr, bool end) :
                ptr(ptr),
                _end(end) {}

        ~rb_iterator_base() {}

        void increment() {
            if (_end)
                _end = false;
            else
                ptr = tree_type::successor(ptr);
            if (ptr->parent == nullptr)
                _end = true;
        }

        void decrement() {
            if (_end)
                _end = false;
            else
                ptr = tree_type::predecessor(ptr);
        }
    };

//--------------------------------- rb_tree forward_iterator --------------------------------
    template<class value_t, class cmp_t, class alloc_t>
    class rb_iterator :
            public rb_iterator_base<value_t, cmp_t, alloc_t> {
    private:
        typedef rb_iterator_base<value_t, cmp_t, alloc_t> base_class;

    public:
        typedef typename base_class::iterator_category iterator_category;
        typedef typename base_class::value_type value_type;
        typedef typename base_class::difference_type difference_type;
        typedef typename base_class::pointer pointer;
        typedef typename base_class::reference reference;
        typedef const reference const_reference;
        typedef const pointer const_pointer;

    public:
        typedef typename base_class::rb_node rb_node;

        rb_iterator(rb_node *ptr, bool end = false) : base_class(ptr, end) {}

        rb_iterator() {}

        rb_iterator(const rb_iterator &cpy) : base_class(cpy) {}

        ~rb_iterator() {}

        rb_iterator &operator++() {
            this->increment();
            return *this;
        }

        rb_iterator operator++(int) {
            rb_iterator ret(*this);
            this->increment();
            return ret;
        }

        rb_iterator &operator--() {
            this->decrement();
            return *this;
        }

        rb_iterator operator--(int) {
            rb_iterator ret(*this);
            this->decrement();
            return ret;
        }

    };

//--------------------------------- rb_tree reverse_iterator --------------------------------
    template<class value_t, class cmp_t, class alloc_t>
    class rb_reverse_iterator :
            public rb_iterator_base<value_t, cmp_t, alloc_t> {
    private:
        typedef rb_iterator_base<value_t, cmp_t, alloc_t> base_class;

    public:
        typedef typename base_class::iterator_category iterator_category;
        typedef typename base_class::value_type value_type;
        typedef typename base_class::difference_type difference_type;
        typedef typename base_class::pointer pointer;
        typedef typename base_class::reference reference;
        typedef const reference const_reference;
        typedef const pointer const_pointer;

    protected:
        typedef typename base_class::rb_node rb_node;

    public:
        rb_reverse_iterator(rb_node *ptr, bool end) : base_class(ptr, end) {}

        rb_reverse_iterator() {}

        rb_reverse_iterator(const rb_reverse_iterator &cmp) : base_class(cmp) {}

        ~rb_reverse_iterator() {}

        rb_reverse_iterator &operator++() {
            this->decrement();
            return *this;
        }

        const rb_reverse_iterator operator++(int) {
            rb_reverse_iterator ret(*this);
            this->decrement();
            return ret;
        }

        rb_reverse_iterator &operator--() {
            this->increment();
            return *this;
        }

        rb_reverse_iterator operator--(int) {
            rb_reverse_iterator ret(*this);
            this->increment();
            return ret;
        }
    };
}
#endif //FT_CONTAINERS_RB_ITERATOR_HPP
