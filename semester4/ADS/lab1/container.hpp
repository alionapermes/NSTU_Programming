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
        member() {}

        member(const T& _value) : value(_value) {}

        member(const T& _value, member* _prev, member* _next)
        : value(_value), prev(_prev), next(_next) {}

        T value;
        member* next = nullptr;
        member* prev = nullptr;
    };

    struct list_iterator
    {
    public:
        using iterator_category = bidirectional_iterator_tag;
        using iterator          = list_iterator;
        using difference_type   = ptrdiff_t;
        using value_type        = T;
        using reference         = value_type&;
        using pointer           = value_type*;

        list_iterator(member* ptr) : m_ptr(ptr) {}

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

    bidir_list(bidir_list& list)
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
    operator=(bidir_list& list)
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

        while ((lhs_it != lhs_it.end()) && (rhs_it != rhs_it.end())) {
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
    { return iterator(last->next); }

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
            first = new member(value, &border, &border);
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
            last  = new member(value, &border, &border);
            first       = last;
            border.next = first;
        } else {
            last->next = new member(value, last, &border);
            last	   = last->next;
        }

        border.prev = last;
        _size++;
    }

    iterator
    find(iterator first, iterator last, const_reference value)
    {
        for (auto it = first; it != last; it++) {
            if (*it == value) {
                return it;
            }
        }

        return last;
    }

private:
    size_t  _size  = 0;
    member* first  = nullptr;
    member* last   = nullptr;
    member  border;
};

