#pragma once

#include <initializer_list>
#include <utility>
#include <iterator>
#include <cstddef>

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
	using iterator				 = list_iterator;
	using const_iterator         = const iterator;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;


	bidir_list(){};

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

	T&
	front()
	{ return first->value; }

	const T&
	front() const
	{ return first->value; }

	T&
	back()
	{ return last->value; }

	const T&
	back() const
	{ return last->value; }

	size_t
	size() const
	{ return _size; }

	void
	push_front(const T& value)
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
	push_back(const T& value)
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

private:
	size_t  _size  = 0;
	member* first  = nullptr;
	member* last   = nullptr;
    member  border;
};

