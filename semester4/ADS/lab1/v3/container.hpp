// Вариант 3 - односвязная структура данных
// на базе массива с индексными указателями

#pragma once

#include <cstddef>
#include <iterator>
#include <exception>
#include <stdexcept>


template<typename T>
class list_v3
{
public:
    struct list_iterator;

    using value_type             = T;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator               = list_iterator;
    using const_iterator         = const list_iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    struct list_iterator
    {
        //
    };

    list_v3() = default;

    list_v3(size_t capacity)
    { reserve(capacity); }

    list_v3(const list_v3<T>& src)
    { *this = src; }

    ~list_v3()
    { clear(); }

    reference
    operator[](size_t pos)
    {
        if (pos >= _cap) {
            std::out_of_range("pos must be less than capacity");
        }

        list_item* item_ptr = _items[pos];
        if (!item_ptr) {
            item_ptr        = new list_item();
            item_ptr->_prev = pos - 1;
            item_ptr->_next = (pos + 1 < _cap ? pos + 1 : -1);

            /* _items[item_ptr->_prev] = */ 
        }

        return item_ptr->_value;
    }

    list_v3<T>&
    operator=(const list_v3<T>& rhs)
    {
        clear();
        _items = new list_item*[rhs._cap];

        _size = rhs._size;
        _cap  = rhs._cap;

        for (size_t n = 0; n < _size; n++) {
            list_item* item_ptr = rhs._items[n];

            if (item_ptr) {
                _items[n] = new list_item(*item_ptr);
            }
        }

        return *this;
    }

    size_type
    size() const
    { return _size; }

    size_type
    capacity() const
    { return _cap; }

    void
    clear()
    {
        for (size_t n = 0; n < _size; n++) {
            delete _items[n];
        }

        delete[] _items;
    }

    void
    reserve(size_t new_cap)
    {
        if (new_cap <= _cap)
            return;

        auto old_ptr = _items;
        _items       = new list_item*[new_cap];
        _cap         = new_cap;

        for (size_t n = 0; n < _cap; n++) {
            if (!old_ptr[n]) {
                _items[n] = new list_item();
                _items[n]->_prev = (n >= 1 ? n - 1 : -1);
                _items[n]->_next = (n + 1 < _cap ? n + 1 : -1);
            } else
                _items[n] = old_ptr[n];
        }

        for (size_t n = 0; n < _size; n++) {
            delete old_ptr[n];
        }
        delete[] old_ptr;
    }

private:
    struct list_item
    {
        friend list_v3;

    public:
        list_item() = default;

        list_item(const_reference value, int prev, int next)
            : _prev(prev), _next(next), _value(value) {}

        list_item(const list_item& item)
            : list_item(item._value, item._prev, item._next) {}

    private:
        int _prev = -1;
        int _next = -1;
        value_type _value;
    };

    size_t _cap        = 0;
    size_t _size       = 0;
    list_item** _items = nullptr;
};

