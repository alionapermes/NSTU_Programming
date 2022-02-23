#pragma once

#include <initializer_list>
#include <utility>
#include <iterator>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <ostream>


template <typename T>
class list_v3
{
public:
    struct member
    {
    public:
        friend class list_v3;

        member() = default;

        member(const T& value) : _value(value) {}

        member(const T& value, int prev, int next)
            : _value(value), _prev(prev), _next(next) {}

    private:
        T _value;
        int _next = -1;
        int _prev = -1;
    };

    struct lisv_v5_iterator
    {
    public:
        friend class list_v3;
        
        using iterator_category = std::bidirectional_iterator_tag;
        using iterator          = lisv_v5_iterator;
        using difference_type   = ptrdiff_t;
        using value_type        = T;
        using reference         = value_type&;
        using pointer           = value_type*;

        lisv_v5_iterator(member* ptr, member* data)
            : _ptr(ptr), _data(data) {}

        iterator&
        operator++()
        {
            _ptr = _ptr->next;
            return *this;
        }

        iterator
        operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator&
        operator--()
        {
            _ptr = _ptr->prev;
            return *this;
        }

        iterator
        operator--(int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

        reference
        operator*()
        { return _ptr->value; }

        pointer
        operator->()
        { return &_ptr->value; }

        friend bool
        operator==(const iterator& lhs, const iterator& rhs)
        { return lhs._ptr == rhs._ptr; }

        friend bool
        operator!=(const iterator& lhs, const iterator& rhs)
        { return lhs._ptr != rhs._ptr; }

    private:
        member* _ptr  = nullptr;
        member* _data = nullptr;
    };

    using value_type             = T;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator				 = lisv_v5_iterator;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    list_v3()
    {   
        _border = new member();
        /* _border->next = _first; */
        /* _border->prev = _last; */
    }

    list_v3(const list_v3& list) : list_v3()
    {
        reserve(list.size());

        for (const auto& item : list) {
            push_back(item);
        }
    }

    ~list_v3()
    {
        clear();
        delete[] _data;
    }

    reference
    operator[](size_t pos)
    {
        if (pos >= _size) {
            throw std::out_of_range("position is out of range");
        }

        return _data[pos].value;
    }

    reference
    operator=(const list_v3& list)
    {
        clear();

        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }

    friend bool
    operator==(const list_v3& lhs, const list_v3& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;

        auto lhs_it = lhs.begin();
        auto rhs_it = rhs.begin();

        while ((lhs_it != lhs.end()) && (rhs_it != rhs.end())) {
            if (*lhs_it != *rhs_it)
                return false;

            lhs_it++;
            rhs_it++;
        }

        return true;
    }

    friend bool
    operator!=(const list_v3& lhs, const list_v3& rhs)
    { return !(lhs == rhs); }

    friend std::ostream&
    operator<<(std::ostream& os, const list_v3& rhs)
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

    iterator
    begin()
    { return iterator(_first, _data); }

    iterator
    end()
    { return iterator(_border, _data); }

    const_iterator
    begin() const
    { return iterator(_first, _data); }

    const_iterator
    end() const
    { return iterator(_border, _data); }

    reverse_iterator
    rbegin()
    { return std::reverse_iterator(end()); }

    reverse_iterator
    rend()
    { return std::reverse_iterator(begin()); }

    reference
    front()
    { return _first->value; }

    const_reference
    front() const
    { return _first->value; }

    reference
    back()
    { return _last->value; }

    const_reference
    back() const
    { return _last->value; }

    size_type
    size() const
    { return _size; }

    bool
    empty() const
    { return _size == 0; }

    void
    clear()
    {
        if (_size == 0)
            return;

        for (size_t n = 0; n < _size; ++n) {
            delete _data[n];
        }
        /* delete[] _data; */

        _size = 0;
    }

    void
    push_front(const_reference value)
    {
        if (_size == 0) {
            _first        = new member(value, _border, _border);
            _last         = _first;
            _border->prev = _last;
        } else {
            _first->prev = new member(value, _border, _first);
            _first       = _first->prev;
        }

        _border->next = _first;
        _size++;
    }

    void
    push_back(const_reference value)
    {
        if (_size == 0) {
            _last         = new member(value, _border, _border);
            _first        = _last;
            _border->next = _first;
        } else {
            _last->next = new member(value, _last, _border);
            _last	    = _last->next;
        }

        _border->prev = _last;
        _size++;
    }

    void
    pop_front()
    {
        if (_size == 0) { return; }

        auto _tmp = _data;

        _data++;
        _first = _data;
        _first->prev = -1;

        delete _tmp;
        _size--;

        /* auto _index   = _first; */
        /* _first        = _first->next; */
        /* _first->prev  = _border; */
        /* _border->next = _first; */

        /* /1* delete ; *1/ */
        /* _size--; */
    }

    void
    pop_back()
    {
        if (_size == 0) { return; }
        
        auto _ptr   = _last;
        _last         = last->prev;
        _last->next   = _border;
        _border->prev = _last;

        delete _ptr;
        _size--;
    }

    iterator
    find(const_reference value) const
    { return find(begin(), end(), value); }

    iterator
    find(iterator _first, iterator _last, const_reference value) const
    {
        for (auto it = _first; it != _last; it++) {
            if (*it == value) {
                return it;
            }
        }

        return _last;
    }

    iterator
    insert(iterator pos, const_reference value)
    {
        if (pos == begin()) {
            push_front(value);
            return iterator(_first);
        } else if (pos == end()) {
            push_back(value);
            return iterator(_last);
        }

        member* m = new member(value, pos._ptr->prev, pos._ptr);
        pos._ptr->prev->next = m;
        pos._ptr->prev       = m;

        _size++;
        return iterator(m);
    }

    iterator
    erase(iterator pos)
    {
        if (pos == end()) { return pos; }

        if (pos._ptr == _first) {
            pop_front();
            return begin();
        } else if (pos._ptr == _last) {
            pop_back();
            return end();
        }

        member* m     = pos._ptr;
        member* next  = m->next;
        m->prev->next = m->next;
        m->next->prev = m->prev;

        delete m;
        _size--;
        
        return iterator(next);
    }

    iterator
    erase(const_reference value)
    { return erase(find(value)); }

private:
    size_t  _size   = 0;
    member* _first  = nullptr;
    member* _last   = nullptr;
    member* _border = nullptr;
    member** _data  = nullptr;
};

