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
private:
    struct list_item;

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
        friend list_v3;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = ptrdiff_t;
        using pointer           = value_type*;
        using const_pointer     = const pointer;

        list_iterator() = default;

        list_iterator(const list_v3* const owner, list_item* ptr)
            : _owner(owner), _ptr(ptr) {}

        iterator&
        operator++()
        {
            if (_ptr->_next < 0)
                _ptr = _owner->_border;
            else
                _ptr = _owner->_items[_ptr->_next];

            return *this;
        }

        iterator
        operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

        reference
        operator*()
        { return _ptr->_value; }

        const_reference
        operator*() const
        { return this->operator*(); }

        pointer
        operator->()
        { return &_ptr->_value; }

        const_pointer
        operator->() const
        { return this->operator->(); }

        friend bool
        operator==(const_iterator& lhs, const_iterator& rhs)
        { return lhs._ptr == rhs._ptr; }

        friend bool
        operator!=(const_iterator& lhs, const_iterator& rhs)
        { return !(lhs == rhs); }

    private:
        const list_v3* const _owner;
        list_item*  _ptr;
    };

    list_v3() = default;

    list_v3(size_t cap)
    { reserve(cap); }

    list_v3(const list_v3<T>& src)
    { *this = src; }

    ~list_v3()
    { clear(); }

    reference
    operator[](size_t pos)
    {
        if (pos >= _capacity)
            std::out_of_range("pos is out of range!");

        list_item*& item_ptr = _items[pos];
        if (!item_ptr) {
            item_ptr = replace(pos);
            _size++;
        }

        return _items[pos]->_value;
    }

    const_reference
    operator[](size_t pos) const
    { return static_cast<list_v3>(*this)[pos]; }

    list_v3<T>&
    operator=(const list_v3<T>& rhs)
    {
        clear();
        allocate(rhs._capacity);

        _size = rhs._size;

        for (size_t n = 0; n < _capacity; n++) {
            list_item* item_ptr = rhs._items[n];

            if (item_ptr)
                _items[n] = new list_item(*item_ptr);
        }

        return *this;
    }

    size_type
    size() const
    { return _size; }

    size_type
    capacity() const
    { return _capacity; }

    void
    clear()
    {
        if (_size == 0 && _capacity == 0)
            return;

        for (size_t n = 0; n < _size; n++)
            delete _items[n];

        delete[] _items;

        _size      = 0;
        _capacity  = 0;
    }

    void
    reserve(size_t new_cap)
    {
        if (new_cap <= _capacity)
            return;

        if (!_items) {
            allocate(new_cap);
            return;
        }

        list_item** old_ptr = _items;
        size_t old_capacity = _capacity;
        allocate(new_cap);

        for (size_t n = 0; n < old_capacity; n++)
            _items[n] = old_ptr[n];

        delete[] old_ptr;
    }

    iterator
    beging()
    { return iterator(this, _first); }

    iterator
    end()
    { return iterator(this, _border); }

    const_iterator
    begin() const
    { return iterator(this, _first); }

    const_iterator
    end() const
    { return iterator(this, _border); }

    reference
    front()
    { return _first->_value; }

    reference
    back()
    { return _last->_value; }

    const_reference
    front() const
    { return _first->_value; }

    const_reference
    back() const
    { return _last->_value; }

    void
    shift(ssize_t pos, ssize_t offset)
    {
        if (pos < 0 || pos >= _capacity)
            throw std::out_of_range("pos is out of range!");

        if (offset == 0)
            return;
        else if (offset > 0)
            shift_front(pos, offset);
        else if (offset < 0)
            shift_back(pos, -offset);
    }

    iterator
    insert(size_t pos, const_reference value)
    {
        if (pos >= _capacity)
            throw std::out_of_range("pos is out of range!");

        reserve(_capacity + 1);
        shift(pos + 1, 1);

        list_item* item_ptr = replace(pos + 1, &value);
        _size++;

        if (item_ptr->_next < 0)
            _last = item_ptr;

        return iterator(this, item_ptr);
    }

    list_item*
    replace(size_t pos, const value_type* value = nullptr)
    {
        if (pos >= _capacity)
            throw std::out_of_range("pos is out of range!");

        int nearest_prev = nearest_index(pos, false);
        auto item_ptr    = new list_item();
        item_ptr->_next  = nearest_index(pos, true);
        
        if (nearest_prev < 0)
            _first = item_ptr;
        else
            _items[nearest_prev]->_next = pos;

        if (item_ptr->_next < 0)
            _last = item_ptr;

        if (value)
            item_ptr->_value = *value;;

        _items[pos] = item_ptr;

        return item_ptr;
    }

    void
    push_back(const_reference value)
    {
        if (_capacity > 0) {
            insert(_capacity - 1, value);
            return;
        }

        reserve(1);
        replace(0, &value);
        _size++;
    }

    void
    push_front(const_reference value)
    {
        reserve(_capacity + 1);
        shift(0, 1);
        replace(0, &value);
        _size++;
    }

    iterator
    erase(iterator pos)
    {
        if (pos == end())
            return end();

        return erase(get_index(pos._ptr));

        /* iterator it = begin(); */

        /* for (; it != pos; ++it) { */
        /*     if (it == end()) */
        /*         return end(); */
        /* } */

        /* size_t index = get_index(it._ptr); */

        /* delete _items[index]; */
        /* _items[index] = nullptr; */
        /* _size--; */

        /* shift(index, -1); */

        /* return iterator(this, _items[index]); */
    }

    iterator
    erase(size_t pos)
    {
        if (pos >= _capacity)
            throw std::out_of_range("pos is out of range!");

        list_item*& item_ptr = _items[pos];

        shift(pos + 1, -1);

        delete item_ptr;
        item_ptr = nullptr;
        _size--;

        return (_size > 0 ? iterator(this, _items[pos]) : end());
    }

private:
    struct list_item
    {
        friend list_v3;

    public:
        list_item() = default;

        list_item(const_reference value, int next)
            : _next(next), _value(value) {}

        list_item(const list_item& item)
            : list_item(item._value, item._next) {}

    private:
        int _next = -1;
        value_type _value;
    };

    size_t _size       = 0;
    size_t _capacity   = 0;
    list_item* _first  = nullptr;
    list_item* _last   = nullptr;
    list_item* _border = nullptr;
    list_item** _items = nullptr;


    void
    allocate(size_t cap)
    {
        _items    = new list_item*[cap]();
        _capacity = cap;
    }

    int
    nearest_index(size_t pos, bool forward)
    {
        if (forward)
            return nearest_forward(pos);
        
        return nearest_backward(pos);
    }

    int
    nearest_forward(size_t pos)
    {
        if (pos + 1 == _capacity)
            return -1;

        for (size_t n = pos + 1; n < _capacity; n++) {
            if (_items[n])
                return n;
        }

        return -1;
    }

    int
    nearest_backward(size_t pos)
    {
        if (pos == 0)
            return -1;

        for (size_t n = pos - 1; n >= 0; n--) {
            if (_items[n])
                return n;
        }

        return -1;
    }

    void
    shift_front(ssize_t pos, ssize_t offset)
    {
        for (ssize_t n = _capacity - 1; n >= pos; n--) {
            if (n + offset < _capacity)
                _items[n + offset] = _items[n];
            else
                delete _items[n];

            _items[n] = nullptr;
        }
    }

    void
    shift_back(ssize_t pos, ssize_t offset)
    {
        for (ssize_t n = 0; n <= pos; n++) {
            if (n - offset >= 0)
                _items[n - offset] = _items[n];
            else
                delete _items[n];

            _items[n] = nullptr;
        }
    }

    size_t
    get_index(const list_item* item_ptr)
    {
        size_t pos;

        for (pos = 0; pos < _capacity; pos++) {
            if (item_ptr == _items[pos])
                break;
        }

        return pos;
    }
};

