#pragma once

#include "tl/expected.hpp"

#include <initializer_list>
#include <utility>
#include <iterator>
#include <cstddef>
#include <ostream>


template<typename T>
class evector
{
public:
    struct iterator;

    enum class error
    {
        out_of_range,
        invalid_param
    };

    using value_type             = T;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    struct iterator
    {
    public:
        using value_type        = T;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = ptrdiff_t;

        iterator(pointer ptr) : _ptr(ptr) {}

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

        auto
        operator<=>(const_iterator& other) const = default;

        iterator
        operator+(size_type offset) const
        { return iterator(_ptr + offset); }

        iterator
        operator-(size_type offset) const
        { return iterator(_ptr - offset); }

    private:
        pointer _ptr = nullptr;
    };

    evector() = default;

    evector(size_type cap) : _size(cap)
    {
        reserve(cap);
        _first = _data;
        _last  = _first + (_size > 0 ? _size - 1 : 0);
    }

    evector(const evector& src)
    { *this = src; }

    evector(evector&& src) noexcept
    { *this = std::move(src); }

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

    evector&
    operator=(const evector& other)
    {
        iterator iter = other.begin();

        reserve(other._capacity);
        _size  = other._size;
        _first = _data;
        _last  = _first + (_size > 0 ? _size - 1 : 0);

        for (size_t n = 0; n < _size; n++)
            _data[n] = *iter++;

        return *this;
    }

    evector&
    operator=(evector&& other) noexcept
    {
        delete[] _data;

        _data     = std::exchange(other._data, nullptr);
        _first    = std::exchange(other._first, nullptr);
        _last     = std::exchange(other._last, nullptr);
        _size     = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, 0);

        return *this;
    }

    friend std::ostream&
    operator<<(std::ostream& os, const evector& rhs)
    {
        size_t n = 0;
        os << "[";

        for (const auto& item : rhs) {
            os << item;
            if (++n < rhs.size())
                os << ", ";
        }

        os << "]";
        return os;
    }


    size_type
    size() const
    { return _size; }

    size_type
    capacity() const
    { return _capacity; }

    bool
    empty() const
    { return !_size; }

    void
    clear()
    {
        _first = nullptr;
        _last  = nullptr;
        _size  = 0;
    }

    void
    reserve(size_type new_cap)
    {
        if (new_cap <= _capacity)
            return;

        pointer old_data  = _data;
        size_type old_cap = _capacity;

        if (auto start_index = get_index(_first))
            shift(*start_index, *start_index + _size, *start_index);

        allocate(new_cap);

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
    { return iterator(_last + 1); }

    const_iterator
    begin() const
    { return iterator(_first); }

    const_iterator
    end() const
    { return iterator(_last + 1); }

    reverse_iterator
    rbegin()
    { return reverse_iterator(end()); }

    reverse_iterator
    rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator
    rbegin() const
    { return const_reverse_iterator(end()); }

    const_reverse_iterator
    rend() const
    { return const_reverse_iterator(begin()); }

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

    tl::expected<size_type, error>
    shift(ssize_t offset)
    { return shift(*get_index(_first), _size, offset); }

    tl::expected<size_type, error>
    shift(size_type start, size_type end, ssize_t offset)
    {
        if (end > _capacity)
            return tl::unexpected(error::out_of_range);

        if (!offset || (start == end))
            return start;

        auto f = (offset < 0 ? &evector::shift_back : &evector::shift_front);
        (this->*f)(start, end, std::abs(offset));

        return start + offset;
    }

    void
    shrink_to_fit()
    {
        size_type index   = 0;
        pointer old_data  = _data;
        iterator iter     = begin();
        iterator iter_end = end();

        allocate(_size);
        _first = _data;
        _last  = _first + _size - 1;

        for (; iter != iter_end; ++iter)
            _data[index++] = *iter;

        delete[] old_data;
    }

    template<typename U>
    void
    push_front(U&& value)
    {
        if (_size == _capacity) {
            reserve(_capacity > 0 ? _capacity << 1 : 1);
            return push_front(std::forward<U>(value));
        }

        if (!_size) {
            _first = _data;
            _last  = _first;
        } else {
            if (_first == _data)
                shift(1);
            _first--;
        }

        *_first = std::forward<U>(value);
        _size++;
    }

    template<typename U>
    void
    push_back(U&& value)
    {
        if (_size == _capacity) {
            reserve(_capacity > 0 ? _capacity << 1 : 1);
            return push_back(std::forward<U>(value));
        }

        if (!_size) {
            _first = _data;
            _last  = _first;
        } else {
            if (_last == (_data + _capacity - 1))
                shift(-1);
            _last++;
        }

        *_last = std::forward<U>(value);
        _size++;
    }

    void
    pop_front()
    {
        _first++;
        _size--;
    }

    void
    pop_back()
    {
        _last--;
        _size--;
    }

private:
    size_type _size     = 0;
    size_type _capacity = 0;
    pointer _data       = nullptr;
    pointer _first      = nullptr;
    pointer _last       = nullptr;

    void
    allocate(size_type cap)
    {
        _data     = new value_type[cap + 1]();
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

        _first += offset;
        _last   = (
            (*get_index(_last) + offset) >= _capacity
            ? _data + (_capacity - 1)
            : _last + offset
        );
    }

    void
    shift_back(size_type start, size_type end, size_type offset)
    {
        for (size_type pos = start; pos < end; pos++) {
            if (pos < offset)
                continue;

            _data[pos - offset] = _data[pos];
        }

        _first  = (*get_index(_first) >= offset ? _first - offset : _data);
        _last  -= offset;
    }

    tl::expected<size_type, error>
    get_index(const_pointer ptr)
    {
        if (!ptr)
            return tl::unexpected(error::invalid_param);

        size_type index = 0;
        while (ptr-- != _data)
            index++;

        return index;
    }
};

