#pragma once

#include <initializer_list>
#include <utility>
#include <iterator>
#include <cstddef>
#include <exception>
#include <stdexcept>


template<typename T>
class evector
{
public:
    struct evector_iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using iterator          = evector_iterator;
        using difference_type   = ptrdiff_t;
        using value_type        = T;
        using reference         = value_type&;
        using pointer           = value_type*;

        evector_iterator(pointer ptr) : m_ptr(ptr) {}

        auto operator++() -> iterator& {
            m_ptr++;
            return *this;
        }

        auto operator++(int) -> iterator {
            iterator old = *this;
            ++(*this);
            return old;
        }

        auto operator--() -> iterator& {
            m_ptr--;
            return *this;
        }

        auto operator--(int) -> iterator {
            iterator old = *this;
            --(*this);
            return old;
        }

        auto operator*() -> reference {
            return *m_ptr;
        }

        auto operator->() -> pointer {
            return m_ptr;
        }

        friend
        auto operator==(const iterator& lhs, const iterator& rhs) -> bool {
            return lhs.m_ptr == rhs.m_ptr;
        }

        friend
        auto operator!=(const iterator& lhs, const iterator& rhs) -> bool {
            return lhs.m_ptr != rhs.m_ptr;
        }

    private:
        pointer m_ptr = nullptr;
    };

    using value_type             = T;
    using size_type              = size_t;
    using pointer                = value_type*;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator               = evector_iterator;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    evector() {}

    evector(size_t __size) : _size(__size) {
        data  = new T[_size];
        first = data;
        last  = data;
    }

    auto operator[](size_type index) -> reference {
        return data[index];
    }

    auto begin() -> iterator {
        return iterator(first);
    }

    auto end() -> iterator {
        return iterator(last);
    }

    auto begin() const -> const_iterator {
        return iterator(first);
    }

    auto end() const -> const_iterator {
        return iterator(last);
    }

    auto rbegin() -> reverse_iterator {
        return reverse_iterator(end());
    }

    auto rend() -> reverse_iterator {
        return reverse_iterator(begin());
    }

    auto rbegin() const -> const_reverse_iterator {
        return const_reverse_iterator(end());
    }

    auto rend() const -> const_reverse_iterator {
        return const_reverse_iterator(begin());
    }

    auto front() -> reference {
        return *first;
    }

    auto back() -> reference {
        return *last;
    }

    auto front() const -> const_reference {
        return *first;
    }

    auto back() const -> const_reference {
        return *last;
    }

    auto size() const -> size_type {
        return _size;
    }

    auto capacity() const -> size_type {
        return _capacity;
    }

    auto empty() const -> bool {
        return _size == 0;
    }

    auto clear() -> void {
        delete[] data;
        data  = nullptr;
        first = nullptr;
        last  = nullptr;
    }

    auto resize(size_type new_size) -> void {
        auto tmp      = new T[new_size];
        auto size_old = _size;

        _capacity = new_size;
        _size     = new_size;

        for (size_type n = 0; ((n < _size) && (n < size_old)); ++n) {
            tmp[n] = data[n];
        }

        delete[] data;
        data  = tmp;
        first = data;
        last  = data + _size - 1;
    }

    auto reserve(size_type new_capacity) -> void {
        //
    }

    auto push_front(const_reference value) -> void {
        if (_size == _capacity) {
            resize((_size == 0 ? 1 : (_capacity << 1)));
        }
        
        shift(1);
        data[0] = value;
    }

    auto push_back(const_reference value) -> void {
        if (_size == 0) {
            resize(1);

            data[0] = value;
            first   = data;
            last    = data;

            return;
        }

        if (_size == _capacity) {
            resize(_capacity << 1);
        }

        data[_size] = value;
        ++last;
    }

    auto pop_front() -> void {
        --_size;
        ++first;
    }

    auto pop_back() -> void {
        --_size;
        --last;
    }

private:
    pointer data        = nullptr;
    pointer first       = nullptr;
    pointer last        = nullptr;
    size_type _size     = 0;
    size_type _capacity = 0;

    auto shift(int offset) -> void {
        if (offset == 0) return;

        if (offset > 0) {
            shift_front(std::abs(offset));
        } else {
            shift_back(std::abs(offset));
        }
    }

    auto shift_front(size_type offset) -> void {
        last += offset;

        for (size_type n = 0; n < _size + offset; ++n) {
            data[n] = data[n + offset];
        }
    }

    auto shift_back(size_type offset) -> void {
        first -= offset;

        for (size_type n = 0; n < _size + offset; ++n) {
            data[n] = data[n - offset];
        }
    }
};

