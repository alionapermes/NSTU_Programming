#pragma once

#include <cstddef>
#include <iterator>

#include "vertex.hpp"
#include "base_iterator.hpp"


namespace coursework {


template <typename T>
struct Edge
{
public: // definitions
    struct EdgeIterator;

    using data_t   = T;
    using vertex_t = Vertex<data_t>;
    using iterator = EdgeIterator;

private: // fields
    std::size_t _weight = 0;
    vertex_t* _v1       = nullptr;
    vertex_t* _v2       = nullptr;
    data_t _data; // wtf??

public: // ctors
    Edge() = delete;

    Edge(vertex_t* v1, vertex_t* v2) : _v1(v1), _v2(v2) {}

    Edge(vertex_t* v1, vertex_t* v2, std::size_t weight)
        : Edge(v1, v2)
        , _weight(weight)
    {}

    Edge(vertex_t* v1, vertex_t* v2, std::size_t weight, const data_t& data)
        : Edge(v1, v2, weight)
        , _data(data)
    {}

public: // getters
    std::size_t
    weight() const
    { return _weight; }

    vertex_t*
    v1() const
    { return _v1; }

    vertex_t*
    v2() const
    { return _v2; }

    const data_t&
    data() const
    { return _data; }

public: // setters
    void
    setWeight(std::size_t weight)
    { _weight = weight; }

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
    struct EdgeIterator : BaseIterator<data_t>
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

