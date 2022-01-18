#pragma once

#include <initializer_list>
#include <utility>
#include <iterator>
#include <cstddef>
#include <exception>
#include <stdexcept>

using namespace std;


template <typename T>
class bidir_list
{
public:
    struct member
    {
    public:
        friend class bidir_list;

        member() {}

        member(const T& _value) : value(_value) {}

        member(const T& _value, member* _prev, member* _next)
        : value(_value), prev(_prev), next(_next) {}

    private:
        T value;
        member* next = nullptr;
        member* prev = nullptr;
    };

    struct list_iterator
    {
    public:
        friend class bidir_list;
        using iterator_category = bidirectional_iterator_tag;
        using iterator          = list_iterator;
        using difference_type   = ptrdiff_t;
        using value_type        = T;
        using reference         = value_type&;
        using pointer           = value_type*;

        list_iterator(member* ptr) : m_ptr(ptr) {}

        list_iterator(const member* ptr) : m_ptr(ptr) {}

        iterator&
        operator++()
        {
            m_ptr = m_ptr->next;
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
            m_ptr = m_ptr->prev;
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
        { return m_ptr->value; }

        pointer
        operator->()
        { return &m_ptr->value; }

        friend bool
        operator==(const iterator& lhs, const iterator& rhs)
        { return lhs.m_ptr == rhs.m_ptr; }

        friend bool
        operator!=(const iterator& lhs, const iterator& rhs)
        { return lhs.m_ptr != rhs.m_ptr; }

    private:
        member* m_ptr = nullptr;
    };

    using value_type             = T;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator				 = list_iterator;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    bidir_list(){}

    ~bidir_list()
    { clear(); }

    bidir_list(const bidir_list& list)
    {
        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }

    bidir_list(const initializer_list<T>& list)
    {
        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }

    reference
    operator[](size_t pos)
    {
        if (pos >= _size) {
            throw out_of_range("position is out of range");
        }

        for (auto it = begin(); it != end(); it++) {
            if (pos-- == 0) { return *it; }
        }

        // never returns
        return *end();
    }

    reference
    operator=(const bidir_list& list)
    {
        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }

    friend bool
    operator==(const bidir_list& lhs, const bidir_list& rhs)
    {
        if (lhs.size() != rhs.size()) { return false; }

        auto lhs_it = lhs.begin();
        auto rhs_it = rhs.begin();

        while ((lhs_it != lhs.end()) && (rhs_it != rhs.end())) {
            if (*lhs_it != *rhs_it) { return false; }
            lhs_it++; rhs_it++;
        }

        return true;
    }

    friend bool
    operator!=(const bidir_list& lhs, const bidir_list& rhs)
    { return !(lhs == rhs); }

    iterator
    begin()
    { return iterator(first); }

    iterator
    end()
    { return iterator(&border); }

    const_iterator
    begin() const
    { return iterator(first); }

    const_iterator
    end() const
    { return iterator(&border); }

    reverse_iterator
    rbegin()
    { return std::reverse_iterator(end()); }

    reverse_iterator
    rend()
    { return std::reverse_iterator(begin()); }

    reference
    front()
    { return first->value; }

    const_reference
    front() const
    { return first->value; }

    reference
    back()
    { return last->value; }

    const_reference
    back() const
    { return last->value; }

    size_type
    size() const
    { return _size; }

    bool
    empty() const
    { return _size == 0; }

    void
    clear()
    {
        if (_size == 0) return;

        for (auto ptr = first->next; ptr != &border; ptr = ptr->next) {
            delete ptr->prev;
        }
        delete last;

        _size = 0;
    }

    void
    push_front(const_reference value)
    {
        if (_size == 0) {
            first       = new member(value, &border, &border);
            last        = first;
            border.prev = last;
        } else {
            first->prev = new member(value, &border, first);
            first       = first->prev;
        }

        border.next = first;
        _size++;
    }

    void
    push_back(const_reference value)
    {
        if (_size == 0) {
            last        = new member(value, &border, &border);
            first       = last;
            border.next = first;
        } else {
            last->next = new member(value, last, &border);
            last	   = last->next;
        }

        border.prev = last;
        _size++;
    }

    void
    pop_front()
    {
        if (_size == 0) { return; }

        member* m   = first;
        first       = first->next;
        first->prev = &border;

        delete m;
        _size--;
    }

    void
    pop_back()
    {
        if (_size == 0) { return; }
        
        member* m  = last;
        last       = last->prev;
        last->next = &border;

        delete m;
        _size--;
    }

    iterator
    find(const_reference value) const
    { return find(begin(), end(), value); }

    iterator
    find(iterator first, iterator last, const_reference value) const
    {
        for (auto it = first; it != last; it++) {
            if (*it == value) {
                return it;
            }
        }

        return last;
    }

    iterator
    insert(iterator pos, const_reference value)
    {
        if (pos == end()) {
            push_back(value);
            return iterator(last);
        }

        if (pos.m_ptr == first) {
            push_front(value);
            return iterator(first);
        }

        member* m = new member(value, pos.m_ptr->prev, pos.m_ptr);
        pos.m_ptr->prev->next = m;
        pos.m_ptr->prev       = m;

        _size++;
        return iterator(m);
    }

    iterator
    erase(iterator pos)
    {
        member* m     = pos.m_ptr;
        member* next  = m->next;
        m->prev->next = m->next;
        m->next->prev = m->prev;

        delete m;
        _size--;
        
        return iterator(next);
    }

    iterator
    erase(const_reference value)
    {
        auto pos = find(value);

        if (pos == end()) { return pos; }
        else { return remove(pos); }
    }

private:
    size_t  _size  = 0;
    member* first  = nullptr;
    member* last   = nullptr;
    member  border;
};

