//
// Created by aregenia on 26.12.22.
//

#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

#include <iostream>
#include <limits>
#include <cstring>
#include "defs.hpp"
#include "iterator.hpp"
#include "normal_iterator.hpp"
#include "type_traits.hpp"
#include "utils.hpp"

namespace ft {

    template<
            class T,
            class Allocator=std::allocator<T>
    >
    class vector {
    public:
        typedef T                                           value_type;
        typedef typename Allocator::pointer                 pointer;
        typedef typename Allocator::const_pointer           const_pointer;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;

        typedef ft::normal_iterator<pointer, vector>        iterator;
        typedef ft::normal_iterator<const_pointer, vector>  const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef Allocator                                   allocator_type;

    private:
        size_type _allocated;
        allocator_type _allocator;
        pointer _begin;
        pointer _end;
    public:

// =======================Constructor======================================
        vector() :
                _allocated(0),
                _allocator(allocator_type()),
                _begin(nullptr),
                _end(nullptr)
        /**
            default vector constructor
            creates empty vector
            time O(1)
            memory O(1)
        */
        {}

// =========================================================================
        explicit vector(const allocator_type &alloc) :
                _allocated(0),
                _allocator(alloc),
                _begin(nullptr),
                _end(nullptr)
        /**
            constructor with explicitly set allocator
            creates empty container
            @param alloc const reference to allocator
            time O(1)
            memory O(1)
        */
        {}

// =========================================================================
        explicit vector(size_type count,
                        const T& value = T(),
                        const allocator_type& alloc = allocator_type()
        ) :
                _allocated(0),
                _allocator(alloc),
                _begin(nullptr),
                _end(nullptr)
        /**
            construct with explicitly set allocator and fill container default value type T or explicitly set value
            @param count size of container
            @param value const reference to the value to be filled container
            @param alloc const reference of allocator
            time O(size)
            memory O(size)
        */
        {
            if (count < _S_max_size(alloc))
                _init(count, false);
            else
                throw (std::length_error("cannot create ft::vector larger than max_size()"));
            _construct(_begin, count, value);
        }

// =========================================================================
#ifndef CPP11
        explicit vector(size_type count) :
                _allocated(0),
                _allocator(allocator_type()),
                _begin(nullptr),
                _end(nullptr)
        /**
            construct with explicitly set allocator
            creates container size of 'size' and fill it default values
            @param size size of container
            @param alloc const reference of allocator
            time O(size)
            memory O(size)
        */
        {
            if (count < _S_max_size(_allocator))
                _init(count);
            else
                throw (std::length_error("cannot create ft::vector larger than max_size()"));
        }
#endif
// =========================================================================
        template<class InputIt>
        vector(InputIt first, InputIt last,
            const Allocator& alloc = Allocator()) :
        _allocated(0),
        _allocator(alloc),
        _begin(nullptr),
        _end(nullptr)
        /**
            constructor with explicitly set allocator
            create vector from gets Input Iterators
            @tparam InputIt type of input iterator
            @param first Input Iterator, will become first element of vector
            @param last Input Iterator, will become last element of vector
            @param alloc const reference to default or explicitly set allocator
            time O(distance(first, last))
            memory O(distance(first, last))
         */
        {
            typedef typename ft::enable_if<ft::is_integral<InputIt>::value, InputIt>::type Integral;
            M_initialize_dispatch(first, last, Integral());
        }
// =========================================================================
        vector(const vector& other) :
        _allocated(0),
        _allocator(allocator_type()),
        _begin(nullptr),
        _end(nullptr)
        /**
            vector copy constructor
            create deep copy container
            @param other const reference to copying container
            time O(other.size())
            memory O(other.size())
         */
        {
            if (other.size() < _S_max_size(_allocator))
            {
                _init(other.size(), false);
                _copy(other._begin, other._end, this->_begin);
            }
        }
// =========================================================================
#ifndef CPP11
        vector(const vector& other, const allocator_type &alloc) :
        _allocated(0),
        _allocator(alloc()),
        _begin(nullptr),
        _end(nullptr)
        /**
            vector copy constructor with explicit set allocator
            create deep copy container
            @param other const reference to copying container
            @param alloc const reference to allocator
            time O(other.size())
            memory O(other.size())
         */
        {
            if (other.size() < _S_max_size(_allocator))
            {
                _init(other.size(), false);
                _copy(other._begin, other._end, this->_begin);
            }
        }
#endif
// =========================================================================
        ~vector()
        /**
            destructor of vector
            destroy all elements of container and deallocate memory vector
            time O(size())
            memory O(1)
        */
        {
            _deallocate();
        }
// =========================================================================
        vector  &operator=(const vector &other)
        /**
            copy operator
            operator destroy current content of vector (and deallocate)
            create deep copy
            @param other const reference to copying vector
            @return reference to created vector
            time O(this->size() + other.size())
            memory O(other.size())
        */
        {
            _deallocate();
            if (other.size() > 0)
            {
                _init(other.size());
                _copy(other._begin, other._end, this->_begin);
            }
            return *this;
        }
// =========================================================================
        void    assign(size_type count, const T &value)
        /**
             Replaces the contents with count copies of value value
             @param count size new vector
             @param value value fill of new vector
             time O(count)
             memory O(count)
         */
        {
            if (count < _S_max_size(_allocator))
            {
                _deallocate();
                _init(count, false);
                _construct(this->_begin, count, value);
            }
            else
                throw (std::length_error("cannot create ft::vector larger than max_size()"));
        }
// =========================================================================
        template<class InputIt>
        void    assign(
                typename ft::enable_if<not ft::is_integral<InputIt>::value, InputIt>::type first,
                InputIt last)
        /**
            Replaces the contents with copies of those in the range [first, last).
            The behavior is undefined if either argument is an iterator into *this.
            @param first first element of new vector
            @param last last element of new vector
            time O(distance(first, last)
            memory O(distance(first, last)
        */
        {
            _deallocate();
            difference_type size = ft::distance(first, last);
            _init(size, false);
            _copy(first, last, _begin);
        }
// =========================================================================
        allocator_type  get_allocator() const
        /**
            getter allocator of container
            @return allocator of container
            time O(1)
            memory O(1)
        */
        {
            return _allocator;
        }
// ================Element access===========================================
        reference   at(size_type pos)
        /**
            get reference to element on position container
            @param pos position of the element to return
            @return Reference to the requested element
            time O(1)
            memory O(1)
        */
        {
            if (this->size() > pos)
                return *(_begin + pos);
            else
                throw std::out_of_range("ft::vector::_M_range_check: __n >= this->size()");
        }
// =========================================================================
        const_reference at(size_type pos) const
        /**
            get const reference to element on position container
            @param pos position of the element to return
            @return const reference to the requested element
            time O(1)
            memory O(1)
        */
        {
            if (this->size() > pos)
                return *(_begin + pos);
            else
                throw std::out_of_range("ft::vector::_M_range_check: __n >= this->size()");
        }
// =========================================================================
        reference   operator[](size_type pos)
        /**
            get reference to element at pos, no bound checking
            @param pos position element of container
            @return reference to request element
            time O(1)
            memory O(1)
        */
        {
            return *(_begin + pos);
        }
// =========================================================================
        const_reference operator[](size_type pos) const
        /**
            get const reference to element at pos, no bound checking
            @param pos position element of container
            @return const reference to request element
            time O(1)
            memory O(1)
        */
        {
            return *(_begin + pos);
        }
// =========================================================================
        reference   front()
        /**
            return reference to the first element of vector
            @return reference to the first element of vector
            time O(1)
            memory O(1)
        */
        {
            return *_begin;
        }
// =========================================================================
        const_reference  front() const
        /**
            return const reference to the first element of vector
            @return const reference to the first element of vector
            time O(1)
            memory O(1)
        */
        {
            return *_begin;
        }
// =========================================================================
        reference   back()
        /**
            return reference to the last element of vector
            @return reference to the last element of vector
            time O(1)
            memory O(1)
        */
        {
            return *(_begin + size() - 1);
        }
// =========================================================================
        const_reference back() const
        /**
            return const reference to the last element of vector
            @return const reference to the last element of vector
            time O(1)
            memory O(1)
        */
        {
            return *(_begin + size() - 1);
        }
// =========================================================================
        T*  data()
        /**
            return pointer to data vector
            @return pointer to data vector
            time O(1)
            memory O(1)
        */
        {
            return _begin;
        }
// =========================================================================
        const T*    data() const
        /**
            return const pointer to data vector
            @return const pointer to data vector
            time O(1)
            memory O(1)
        */
        {
            return _begin;
        }
// ==================Iterators=============================================
        iterator    begin()
        /**
            return iterator object to begin of vector
            @return iterator begin
            time O(1)
            memory O(1)
        */
        {
            return iterator(_begin);
        }
// =========================================================================
        const_iterator  begin() const
        /**
            return const iterator object to begin of vector
            @return const iterator begin
            time O(1)
            memory O(1)
        */
        {
            return const_iterator(_begin);
        }
// =========================================================================
        iterator    end()
        {
            /**
                return iterator object to end of vector
                @return iterator end
                time O(1)
                memory O(1)
            */
            return iterator(_end);
        }
// =========================================================================
        const_iterator  end() const
        /**
            return const iterator object to end of vector
            @return const iterator end
            time O(1)
            memory O(1)
        */
        {
            return const_iterator(_end);
        }
// =========================================================================
        reverse_iterator    rbegin()
        /**
            return reverse iterator object to end of vector
            @return reverse iterator of vector
            time O(1)
            memory O(1)
         */
        {
            return reverse_iterator(end());
        }
// =========================================================================
        const_reverse_iterator  rbegin() const
        /**
            return const reverse iterator object to end of vector
            @return const reverse iterator of vector
            time O(1)
            memory O(1)
         */
        {
            return const_reverse_iterator(end());
        }
// =========================================================================
        reverse_iterator    rend()
        /**
            return reverse iterator object to begin of vector
            @return reverse iterator of vector
            time O(1)
            memory O(1)
         */
        {
            return reverse_iterator(begin());
        }
// =========================================================================
        const_reverse_iterator    rend() const
        /**
            return const reverse iterator object to begin of vector
            @return const reverse iterator of vector
            time O(1)
            memory O(1)
         */
        {
            return const_reverse_iterator(begin());
        }
// ==================Capacity===============================================
        bool    empty() const
        /**
            checks if the vector has no elements
            @return true if vector is empty else false
            time O(1)
            memory O(1)
        */
        {
            return _begin == _end;
        }
// =========================================================================
        size_type   size() const
        /**
            return the number of elements in the vector
            @return number elements
            time O(1)
            memory O(1)
        */
        {

            return  _end - _begin;
        }
// =========================================================================
        size_type   max_size() const
        /**
            return maximum number of elements the vector
            @return maximum number of elements
            time O(1)
            memory O(1)
        */
        {

            return _S_max_size(this->_allocator);
        }
// =========================================================================
        void    reserve(size_type new_cap)
        /**
            reallocate memory if new_cap > 0 and < max_size
            @new_cap size allocate new memory
            time O(size())
            memory O(new_cap)
        */
        {
            if (new_cap > _allocated)
            {
                if (new_cap <= _S_max_size(this->_allocator))
                    _reallocate(new_cap);
                else
                    throw std::length_error("vector::reserve");
            }
        }
// =========================================================================
        size_type   capacity() const
        /**
            return allocated size memory
            @return allocated size memory
            time O(1)
            memory O(1)
        */
        {

            return _allocated;
        }
// ====================Modifiers============================================
        void    clear()
        /**
            destroy elements the vector
            time O(size())
            memory O(1)
        */
        {
            _deallocate(false);
        }
// =========================================================================
        iterator    insert(iterator pos, const T& value)
        /**
            inserts value before pos
            @param pos 	iterator before which the content will be inserted
            @param value element value to insert
            @return Iterator pointing to the inserted value
            time O(distance(pos, end))
            memory O(capacity + 1)
        */
        {
            if (_begin == nullptr)
            {
                _init(1, false);
                _construct_at(_begin, value);
                return begin();
            }
            pointer start = _insert(const_cast<pointer>(pos.base()));
            *start = value;
            return iterator(start);
        }
// =========================================================================
        iterator    insert(iterator pos,
                            size_type count,
                            const_reference value)
        /**
            inserts count copies of the value before pos
            @param pos iterator before which the content will be inserted
            @param count number of elements to insert
            @param value element value to insert
            time O(count + distance(pos, end))
            memory O(capacity + count)
        */
        {
            if (count > _S_max_size(_allocator) || count == 0)
                return _end;
            if (_begin == nullptr)
            {
                _init(count, false);
                _construct(_begin, count, value);
                return _begin;
            }
            pointer ptr = const_cast<pointer>(pos.base());
            pointer start = _insert(ptr, count);
//            difference_type movable = ft::min(_end - ptr, count);
            for (size_type i = 0; i < count; ++i)
                start[i] = value;
            return iterator(start);
//            for (size_type i = movable; i < count; ++i)
//                _construct_at(start, value);
        }
// =========================================================================
        template<class InputIt>
        iterator    insert(iterator pos, InputIt first, InputIt last)
        {
            if (_begin == nullptr)
            {
                assign(first, last);
                return _begin;
            }
            difference_type size = ft::distance(first, last);
            pointer ptr = const_cast<pointer>(pos.base());
            difference_type movable = ft::min(first - ptr, size);
            pointer begin = _insert(ptr, size);
            InputIt non_movable = _move(first, begin, movable);
            _copy(non_movable, last, begin + movable);
            return begin;
        }
// =========================================================================
        iterator    erase(iterator pos)
        {
            if (pos == end())
                return end();
            pointer fin = _erase(const_cast<pointer>(pos.base()));
            return iterator(fin);
        }
// =========================================================================
        iterator    erase(iterator first, iterator last)
        {
            size_type count = ft::distance(first, last);
            if (count > _S_max_size(_allocator) || count == 0)
                return last;
            pointer fin = _erase(const_cast<pointer>(first.base()), count);
            return iterator(fin);
        }
// =========================================================================
        void    push_back(const T& value)
        {
            _append();
            _construct_at(_end++, value);
        }
// =========================================================================
        void    pop_back()
        {
            destroy_at(_end - 1);
            _pop();
        }
// =========================================================================
        void    resize(size_type count)
        {
            if (count > _S_max_size(_allocator))
                throw std::length_error("ft::vector::resize");
            size_type size = this->size();
            if (count > _allocated)
            {
                _alloc_more(count);
                difference_type new_elems = count - size;
                _construct(_begin + size, new_elems);
            }
            else
                _pop(_allocated - count);
            _end = _begin + count;
        }
// =========================================================================
        void    resize(size_type count, T value = T())
        {
            if (count > _S_max_size(_allocator))
                throw std::length_error("ft::vector::resize");
            size_type size = this->size();
            if (count > _allocated)
            {
                _alloc_more(count);
                difference_type new_elems = count - size;
                _construct(_begin + size, new_elems, value);
            }
            else
                _pop(_allocated - count);
            _end = _begin + count;
        }
// =========================================================================
        void    swap(vector &other)
        {
            std::swap(_allocated, other._allocated);
            std::swap(_allocator, other._allocator);
            std::swap(_begin, other._begin);
            std::swap(_end, other._end);
        }
// =========================================================================
    private:
        void    _reallocate(size_type new_size)
        {
            try
            {
                pointer new_begin = _allocator.allocate(new_size);
                memset(static_cast<void *>(new_begin), 0, new_size);

                _copy(_begin, _end, new_begin);
                difference_type size = _end - _begin;
                _deallocate();
                _allocated = new_size;
                _begin = new_begin;
                _end = _begin + size;
            }
            catch (std::exception &)
            {
                _deallocate();
                throw ;
            }
        }

        void _construct_at(pointer ptr, const_reference val)
        {
            _allocator.construct(ptr, val);
        }

        void _construct(pointer start,
                        size_type size,
                        const_reference val = value_type())
        {
            while (size--)
                _construct_at(start++, val);
        }

        void _init(size_type size, bool do_construct = true) {
            // initialization vector - allocate and construct @size elements
            size_type allocated_cap = static_cast<size_type>(size);
            pointer P_ptr;
            try {
                P_ptr = _allocator.allocate(allocated_cap);
                memset(P_ptr, 0, allocated_cap);
            }
            catch (std::bad_alloc &) {
                _deallocate();
                throw;
            }
            _allocated = allocated_cap;
            _begin = P_ptr;
            _end = _begin + _allocated;
            if (do_construct)
                _construct(_begin, size);
        }

        void    _copy(const_pointer src_begin, const_pointer src_end, pointer dst)
        {
            size_type size = src_end - src_begin;
            if (size > _S_max_size(_allocator) || size == 0)
                return;
            _copy(src_begin, dst, size);
        }

        void    _copy(const_pointer src_ptr,
                      pointer dst,
                      size_type cnt)
        {
            if (cnt > _S_max_size(_allocator) || cnt == 0)
                return;
            pointer src = const_cast<pointer>(src_ptr);
            if (dst < src) {
                while (cnt-- > 0)
                    _construct_at(dst++, *src++);
            }
            else if (dst > src)
            {
                dst += cnt;
                src += cnt;
                while (cnt--)
                    _construct_at(--dst, *--src);
            }
        }

        pointer _insert(pointer ptr, difference_type count=1)
        {
            _append(count);
            difference_type move_cnt = (_end - ptr) - count;
            if (move_cnt <= 0)
                _copy(ptr, ptr + count, _end - ptr);
            else
            {
                _copy(ptr + move_cnt, _end, count);
                _move(ptr, ptr + count, move_cnt);
            }
            _end += count;
            return ptr;
        }

        void    _move(pointer src, pointer dst, difference_type cnt)
        {
            if (cnt <= 0)
                return;
            if (src > dst)
            {
                while (cnt-- > 0)
                    *dst++ = *src++;
            }
            else if (dst > src)
            {
                dst += cnt;
                src += cnt;
                while (cnt-- > 0)
                    *(--dst) = *(--src);
            }
        }

        template<class IterT>
        IterT   _move(IterT src, pointer dst, difference_type cnt)
        {
            while (cnt-- > 0)
            {
                *dst = *src;
                ++dst;
                ++src;
            }
            return src;
        }

        void    _alloc_more(size_type least)
        {
            _reallocate(least);
            _allocated = least;
        }

        void    _append(difference_type count=1)
        {
            size_type s = static_cast<size_type>(count);
            if ((size() + s) > _allocated)
                _alloc_more(size() + s);
        }

        pointer _erase(pointer ptr, difference_type count = 1)
        {
            difference_type idx = ptr - _begin;
            difference_type move_cnt = (_end - ptr) - count;
            _move(ptr + count, ptr, move_cnt);
            destroy(_end - count, count);
            _end -= count;
            return _begin + idx;
        }

        void    _pop(difference_type count = 1)
        {
            _end -= count;
        }

        size_type calculate_capacity(size_type capacity) {
            return capacity;
        }

        void _deallocate(bool do_deallocate = true) {
            size_type size = this->size();
            while (size-- > 0)
                destroy_at(--_end);
            if (do_deallocate && _allocated) {
                size_type deallocate_size = static_cast<size_type>(_allocated);
                _allocator.deallocate(_begin, deallocate_size);
                _allocated = 0;
                _begin = nullptr;
                _end = nullptr;
            }
        }

        void destroy_at(pointer ptr) {
            _allocator.destroy(ptr);
        }

        void    destroy(pointer start, difference_type cnt)
        {
            while (cnt -- > 0)
                destroy_at(start++);
        }

        static size_type _S_max_size(const allocator_type& alloc)
        {
            const std::size_t __diffmax = std::numeric_limits<std::ptrdiff_t>::max() / sizeof(T);
            const std::size_t __allocmax = alloc.max_size();
            return std::min(__diffmax, __allocmax);
        }

        template<class InputInteger>
        void
        M_range_initialize(InputInteger first, InputInteger last,
                           ft::input_iterator_tag)
        {
            try {
                for (; first != last; ++first)
                    push_back(*first);
            } catch (...) {
                clear();
                throw;
            }
        }

        template <class Integer>
        void
        M_initialize_dispatch(Integer n, Integer value, ft::true_type)
        {
            size_type s = static_cast<size_type>(n);
            if (s < _S_max_size(_allocator))
                _init(s, false);
            else
                throw (std::length_error("cannot create ft::vector larger than max_size()"));
            _construct(_begin, s, static_cast<value_type>(value));
        }

        template <class InputIterator>
        void
        M_initialize_dispatch(InputIterator first, InputIterator last,
                              ft::false_type)
        {
            M_range_initialize(first, last, ft::_iterator_category(first));
        }

    };
}
#endif //FT_CONTAINERS_VECTOR_H
