//
// Created by aregenia on 12.01.23.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>
#include "defs.hpp"

namespace ft {

    struct input_iterator_tag {
    };
    struct output_iterator_tag {
    };
    struct forward_iterator_tag : public input_iterator_tag {
    };
    struct bidirectional_iterator_tag : public forward_iterator_tag {
    };
    struct random_access_iterator_tag : public bidirectional_iterator_tag {
    };

    template<class Category, class Tp, class Distance = std::ptrdiff_t,
            class Pointer = Tp *, class Reference = Tp &>
    struct iterator {
        typedef Category iterator_category;
        typedef Tp value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    };

    template<class Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef difference_type distance_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template<class Tp>
    struct iterator_traits<Tp *> {
        typedef random_access_iterator_tag iterator_category;
        typedef Tp value_type;
        typedef std::ptrdiff_t difference_type;
        typedef Tp *pointer;
        typedef Tp &reference;
    };

    template<class Tp>
    struct iterator_traits<const Tp *> {
        typedef random_access_iterator_tag iterator_category;
        typedef Tp value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const Tp *pointer;
        typedef const Tp &reference;
    };

    template<class Iterator>
    class reverse_iterator : public iterator<
            typename iterator_traits<Iterator>::iterator_category,
            typename iterator_traits<Iterator>::value_type,
            typename iterator_traits<Iterator>::distance_type,
            typename iterator_traits<Iterator>::pointer,
            typename iterator_traits<Iterator>::reference
    > {
//        template<class Iter>
//        friend class reverse_iterator;
    protected:
        Iterator current;

        typedef iterator_traits<Iterator> _traits_type;

    public:
        typedef Iterator iterator_type;
        typedef typename _traits_type::pointer pointer;
        typedef typename _traits_type::difference_type difference_type;
        typedef typename _traits_type::reference reference;

        reverse_iterator() : current() {}

        explicit reverse_iterator(iterator_type _x) : current(_x) {}

        reverse_iterator(const reverse_iterator &_x) : current(_x.current) {}

        template<class Iter>
        reverse_iterator(const reverse_iterator<Iter> &_x) :
                current(_x.current) {}

        inline iterator_type base() const { return current; }

        reference operator*() const {
            Iterator _tmp = current;
            return *--_tmp;
        }

        pointer operator->() const {
            Iterator _tmp = current;
            --_tmp;
            return S_to_pointer(_tmp);
        }

        reverse_iterator &operator++() {
            --current;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator _tmp = *this;
            --current;
            return _tmp;
        }

        reverse_iterator &operator--() {
            ++current;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator _tmp = *this;
            ++current;
            return _tmp;
        }

        reverse_iterator operator+(difference_type _n) const { return reverse_iterator(current - _n); }

        reverse_iterator &operator+=(difference_type _n) {
            current -= _n;
            return *this;
        }

        reverse_iterator operator-(difference_type _n) const { return reverse_iterator(current + _n); }

        reverse_iterator &operator-=(difference_type _n) {
            current += _n;
            return *this;
        }

        reference operator[](difference_type _n) const { return *(*this + _n); }

        template<class Tp>
        Tp *S_to_pointer(Tp *_p) { return _p; }

        template<class Tp>
        pointer S_to_pointer(Tp _t) { return _t.operator->(); }
    };

#if low_CPP17

    template<class Iterator>
    inline bool operator==(const reverse_iterator<Iterator> &l,
                           const reverse_iterator<Iterator> &r) { return l.base() == r.base(); }

    template<class Iterator>
    inline bool operator<(const reverse_iterator<Iterator> &l,
                          const reverse_iterator<Iterator> &r) { return l.base() < r.base(); }

    template<class Iterator>
    inline bool operator!=(const reverse_iterator<Iterator> &l,
                           const reverse_iterator<Iterator> &r) { return !(l == r); }

    template<class Iterator>
    inline bool operator>(const reverse_iterator<Iterator> &l,
                          const reverse_iterator<Iterator> &r) { return r < l; }

    template<class Iterator>
    inline bool operator<=(const reverse_iterator<Iterator> &l,
                           const reverse_iterator<Iterator> &r) { return !(r < l); }

    template<class Iterator>
    inline bool operator>=(const reverse_iterator<Iterator> &l,
                           const reverse_iterator<Iterator> &r) { return !(l < r); }

// Comparison of reverse_iterator to const reverse_iterator.

    template<class IteratorL, class IteratorR>
    inline bool operator==(const reverse_iterator<IteratorL> &l,
                           const reverse_iterator<IteratorR> &r) { return l.base() == r.base(); }

    template<class IteratorL, class IteratorR>
    inline bool operator<(const reverse_iterator<IteratorL> &l,
                          const reverse_iterator<IteratorR> &r) { return l.base() > r.base(); }

    template<class IteratorL, class IteratorR>
    inline bool operator!=(const reverse_iterator<IteratorL> &l,
                           const reverse_iterator<IteratorR> &r) { return l.base() != r.base(); }

    template<class IteratorL, class IteratorR>
    inline bool operator>(const reverse_iterator<IteratorL> &l,
                          const reverse_iterator<IteratorR> &r) { return l.base() < r.base(); }

    template<class IteratorL, class IteratorR>
    inline bool operator<=(const reverse_iterator<IteratorL> &l,
                           const reverse_iterator<IteratorR> &r) { return l.base() >= r.base(); }

    template<class IteratorL, class IteratorR>
    inline bool operator>=(const reverse_iterator<IteratorL> &l,
                           const reverse_iterator<IteratorR> &r) { return l.base() <= r.base(); }

#endif

    template<class Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &l,
              const reverse_iterator<Iterator> &r) { return r.base() - l.base(); }

    template<class IteratorL, class IteratorR>
    inline typename reverse_iterator<IteratorL>::difference_type
    operator-(const reverse_iterator<IteratorL> &l,
              const reverse_iterator<IteratorR> &r) { return r.base() - l.base(); }

    template<class Iterator>
    inline reverse_iterator<Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n,
              reverse_iterator<Iterator> &i) { return reverse_iterator<Iterator>(i.base() - n); }
    //-----------------------------------------------------------------------------------------
    template<typename InputIterator>
    inline typename ft::iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first, InputIterator last,
              ft::input_iterator_tag) {
        typename ft::iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    }

    template<typename RandomAccessIterator>
    inline typename ft::iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first, RandomAccessIterator last,
              random_access_iterator_tag)
    {
        return last - first;
    }

    template<typename RandomAccessIterator>
    inline typename ft::iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first, RandomAccessIterator last,
              std::random_access_iterator_tag)
    {
        return last - first;
    }

    template<class Iter>
    inline typename ft::iterator_traits<Iter>::iterator_category
    _iterator_category(const Iter&)
    {return typename ft::iterator_traits<Iter>::iterator_category();}


    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last) {
        return ft::_distance(first, last, ft::_iterator_category(first));
    }

//template< class Container>
//class insert_iterator :
//    public ft::iterator<ft::output_iterator_tag, void, void, void, void>
//{
//    typedef typename Container::iterator    Iter;
//
//protected:
//    Container*  container;
//    Iter    iter;
//
//public:
//    typedef Container   container_type;
//
//    insert_iterator(Container &x, Iter i) : container()
//};
}
#endif //FT_CONTAINERS_ITERATOR_HPP
