#pragma once

#include "tl/expected.hpp"

#include <initializer_list>
#include <optional>
#include <utility>
#include <iterator>
#include <cstddef>


enum class evector_error
{
    out_of_range
};

template<typename T>
class evector
{
public:
    struct evector_iterator;
    /* enum class evector_error; */

    using value_type             = T;
    using error                  = evector_error;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = evector_iterator;
    using const_iterator         = const evector_iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    struct evector_iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = ptrdiff_t;

        evector_iterator(pointer ptr) : _ptr(ptr) {}

        iterator&
        operator++()
        {
            _ptr++;
            return *this;
        }

        iterator
        operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

        iterator&
        operator--()
        {
            _ptr--;
            return *this;
        }

        iterator
        operator--(int)
        {
            auto old = *this;
            --(*this);
            return old;
        }

        reference
        operator*()
        { return *_ptr; }

        const_reference
        operator*() const
        { return *_ptr; }

        pointer
        operator->()
        { return _ptr; }

        const_pointer
        operator->() const
        { return _ptr; }

        friend bool
        operator==(const_iterator& lhs, const_iterator& rhs)
        { return lhs._ptr == rhs._ptr; }

        friend bool
        operator!=(const_iterator& lhs, const_iterator& rhs)
        { return lhs.m_ptr != rhs.m_ptr; }

    private:
        pointer _ptr = nullptr;
    };

    evector() = default;

    evector(size_type cap)
    { reserve(cap); }

    evector(const evector& src)
    { *this = src; }

    evector(evector&& src)
        : _size(src._size)
        , _capacity(src._capacity)
        , _data(std::exchange(src._data,   nullptr))
        , _first(std::exchange(src._first, nullptr))
        , _last(std::exchange(src._last,   nullptr)) {}

    ~evector()
    {
        clear();
        delete[] _data;
    }

    reference
    operator[](size_type pos)
    { return _first[pos]; }

    const_reference
    operator[](size_type pos) const
    { return _first[pos]; }

    size_type
    size() const
    { return _size; }

    size_type
    capacity() const
    { return _capacity; }

    void
    clear()
    { _size = 0; }

    void
    reserve(size_type new_cap)
    {
        if (new_cap <= _capacity)
            return;

        pointer old_data  = _data;
        size_type old_cap = _capacity;

        allocate(new_cap);
        _first = _data;
        _last  = _first + _size;

        if (!old_data)
            return;

        for (size_type n = 0; n < old_cap; n++)
            _data[n] = old_data[n];

        delete[] old_data;
    }

    tl::expected<pointer, error>
    at(size_type pos)
    {
        if (pos >= _capacity)
            return tl::unexpected(error::out_of_range);

        return _first + pos;
    }

    tl::expected<const_pointer, error>
    at(size_type pos) const
    {
        if (pos >= _capacity)
            return tl::unexpected(error::out_of_range);

        return _first + pos;
    }

    iterator
    begin()
    { return iterator(_first); }

    iterator
    end()
    { return iterator(_border); }

    const_iterator
    begin() const
    { return iterator(_first); }

    const_iterator
    end() const
    { return iterator(_border); }

    reference
    front()
    { return *_first; }

    reference
    back()
    { return *_last; }

    const_reference
    front() const
    { return *_first; }

    const_reference
    back() const
    { return *_last; }

    tl::expected<size_t, error>
    shift(size_type start, size_type end, ssize_t offset)
    {
        if (end > _capacity)
            return tl::unexpected(error::out_of_range);

        if (!offset || (start == end))
            return start;

        auto f = (offset < 0 ? &evector::shift_back : &evector::shift_front);
        f(std::abs(offset));

        return start + offset;
    }

private:
    value_type _border;
    size_type _size     = 0;
    size_type _capacity = 0;
    pointer _data       = nullptr;
    pointer _first      = nullptr;
    pointer _last       = nullptr;

    void
    allocate(size_type cap)
    {
        _data     = new value_type[cap]();
        _capacity = cap;
    }

    void
    shift_front(size_type start, size_type end, size_type offset)
    {
        size_type pos = end - 1;

        do {
            if (pos + offset >= _capacity)
                continue;

            _data[pos + offset] = _data[pos];
        } while (pos-- > start);
    }

    void
    shift_back(size_type start, size_type end, size_type offset)
    {
        for (size_type pos = start; pos < end; pos++) {
            if (pos < offset)
                continue;

            _data[pos - offset] = _data[pos];
        }
    }
};

