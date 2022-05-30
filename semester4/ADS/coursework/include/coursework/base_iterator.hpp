#pragma once

#include <cstddef>


namespace coursework {


template <typename T>
struct BaseIterator
{
public: // definitions
    using value_type      = T;
    using pointer         = value_type*;
    using reference       = value_type&;
    using difference_type = std::ptrdiff_t;

protected: // fields
    pointer _ptr;

public: // ctors
    BaseIterator(const pointer ptr) : _ptr(ptr) {}

    BaseIterator(const BaseIterator& other) : BaseIterator(other._ptr) {}

public: // operators
    virtual BaseIterator&
    operator++() = 0;

    reference
    operator*()
    { return *_ptr; }
};


}

