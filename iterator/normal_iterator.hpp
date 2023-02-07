//
// Created by aregenia on 15.01.23.
//

#ifndef FT_CONTAINERS_NORMAL_ITERATOR_HPP
#define FT_CONTAINERS_NORMAL_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    template<class Iterator, class Container>
    class normal_iterator {
    protected:
        Iterator current;

        typedef iterator_traits<Iterator> traits_type;

    public:
        typedef Iterator iterator_type;
        typedef typename traits_type::iterator_category iterator_category;
        typedef typename traits_type::value_type value_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::reference reference;
        typedef typename traits_type::pointer pointer;

        normal_iterator() : current(Iterator()) {}

        explicit normal_iterator(const Iterator &copy) : current(copy) {}

        // Forward iterator requirements
        reference operator*() const { return *current; }

        pointer operator->() const { return current; }

        normal_iterator &operator++() {
            ++current;
            return *this;
        }

        normal_iterator operator++(int) { return normal_iterator(current++); }

        // Bidirectional iterator requirements
        normal_iterator &operator--() {
            --current;
            return *this;
        }

        normal_iterator operator--(int) { return normal_iterator(current--); }

        // Random access iterator requirements
        reference operator[](difference_type n) const { return current[n]; }

        normal_iterator &operator+=(difference_type n) {
            current += n;
            return *this;
        }

        normal_iterator operator+(difference_type n) const {
            return normal_iterator(current + n);
        }

        normal_iterator &operator-=(difference_type n) {
            current -= n;
            return *this;
        }

        normal_iterator operator-(difference_type n) const {
            return normal_iterator(current - n);
        }

        const Iterator &base() const { return current; }
    };

// Forward iterator requirements
    template<class IteratorL, class IteratorR, class Container>
    inline bool operator==(const normal_iterator<IteratorL, Container> &l,
                           const normal_iterator<IteratorR, Container> &r) {
        return l.base() == r.base();
    }

    template<class Iterator, class Container>
    inline bool operator==(const normal_iterator<Iterator, Container> &l,
                           const normal_iterator<Iterator, Container> &r) {
        return l.base() == r.base();
    }

    template<class IteratorL, class IteratorR, class Container>
    inline bool operator!=(const normal_iterator<IteratorL, Container> &l,
                           const normal_iterator<IteratorR, Container> &r) {
        return l.base() != r.base();
    }

    template<class Iterator, class Container>
    inline bool operator!=(const normal_iterator<Iterator, Container> &l,
                           const normal_iterator<Iterator, Container> &r) {
        return l.base() != r.base();
    }

// Random access iterator requirements
    template<class IteratorL, class IteratorR, class Container>
    inline bool operator<(const normal_iterator<IteratorL, Container> &l,
                          const normal_iterator<IteratorR, Container> &r) {
        return l.base() < r.base();
    }

    template<class Iterator, class Container>
    inline bool operator<(const normal_iterator<Iterator, Container> &l,
                          const normal_iterator<Iterator, Container> &r) {
        return l.base() < r.base();
    }

    template<class IteratorL, class IteratorR, class Container>
    inline bool operator>(const normal_iterator<IteratorL, Container> &l,
                          const normal_iterator<IteratorR, Container> &r) {
        return l.base() > r.base();
    }

    template<class Iterator, class Container>
    inline bool operator>(const normal_iterator<Iterator, Container> &l,
                          const normal_iterator<Iterator, Container> &r) {
        return l.base() > r.base();
    }

    template<class IteratorL, class IteratorR, class Container>
    inline bool operator<=(const normal_iterator<IteratorL, Container> &l,
                           const normal_iterator<IteratorR, Container> &r) {
        return l.base() <= r.base();
    }

    template<class Iterator, class Container>
    inline bool operator<=(const normal_iterator<Iterator, Container> &l,
                           const normal_iterator<Iterator, Container> &r) {
        return l.base() <= r.base();
    }

    template<class IteratorL, class IteratorR, class Container>
    inline bool operator>=(const normal_iterator<IteratorL, Container> &l,
                           const normal_iterator<IteratorR, Container> &r) {
        return l.base() >= r.base();
    }

    template<class Iterator, class Container>
    inline bool operator>=(const normal_iterator<Iterator, Container> &l,
                           const normal_iterator<Iterator, Container> &r) {
        return l.base() >= r.base();
    }

    template<class IteratorL, class IteratorR, class Container>
    inline typename normal_iterator<IteratorL, Container>::difference_type
    operator-(const normal_iterator<IteratorL, Container> &l,
              const normal_iterator<IteratorR, Container> &r) {
        return l.base() - r.base();
    }

    template<class Iterator, class Container>
    inline typename normal_iterator<Iterator, Container>::difference_type
    operator-(const normal_iterator<Iterator, Container> &l,
              const normal_iterator<Iterator, Container> &r) {
        return l.base() - r.base();
    }

    template<class Iterator, class Container>
    inline normal_iterator<Iterator, Container>
    operator+(typename normal_iterator<Iterator, Container>::difference_type n,
              const normal_iterator<Iterator, Container> &i) {
        return normal_iterator<Iterator, Container>(i.base() + n);
    }
}
#endif //FT_CONTAINERS_NORMAL_ITERATOR_HPP
