#pragma once

#include <cstddef>
#include <iterator>
#include <string>
#include <string_view>

#include "base_iterator.hpp"


namespace coursework {


template <typename T>
struct Vertex
{
public: // definitions
    struct VertexIterator;

    using data_t   = T;
    using iterator = VertexIterator;

private: // fields
    int _index = -1;
    std::string _name;
    data_t _data;

public: // getters
    std::string
    name() const
    { return _name; }

    const data_t&
    data() const
    { return _data; }

public: // setters
    void
    setName(std::string_view name)
    { _name = name; }

    void
    setData(const data_t& data)
    { _data = data; }

public: // user methods
    iterator
    begin()
    {
        // todo…
    }

    iterator
    end()
    {
        // todo…
    }

public: // sub structs
    struct VertexIterator : BaseIterator<data_t>
    {
    public: // definitions
        using base              = BaseIterator<data_t>;
        using iterator_category = std::forward_iterator_tag;

    public: // operators
        base&
        operator++() override
        {
            // todo…
        }
    };
};


}

