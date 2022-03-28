#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>


template <typename Key, typename Compare = std::less<Key>>
class bst
{
public: // definitions
    struct bst_iterator;

private: // definitions
    struct node;

public: // aliases
    using value_type             = Key;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = bst_iterator;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using node_type              = node;

public:
    struct bst_iterator
    {
    private: // fields
        node_type* _ptr;

    public: // ctors
        explicit bst_iterator(node_type* ptr) : _ptr(ptr) {}

        bst_iterator(const_iterator& other) : bst_iterator(other._ptr) {}

    public: // operators
        iterator&
        operator++();

        iterator
        operator++(int);

        iterator&
        operator--();

        iterator
        operator--(int);

        reference
        operator*();

        const_reference
        operator*() const;

        pointer
        operator->();

        const_pointer
        operator->() const;

        auto
        operator<=>(const_iterator& other) const = default;
    };

private:
    struct node
    {
    private: // fields
        value_type _value;
        node_type* _left  = nullptr;
        node_type* _right = nullptr;

    public: // ctors
        node() = default;

        template <typename T>
        explicit node(
            T&& value,
            node_type* left  = nullptr,
            node_type* right = nullptr
        )
            : _value(std::forward<Key>(value))
            , _left(left)
            , _right(right) {}

    public: // operators
        auto
        operator<=>(const node& other) const;
    };

private: // fields
    size_type _size  = 0;
    node_type* _root = nullptr;

public: // ctors
    bst() = default;

    bst(const bst& other);

    bst(bst&& other)
        : _root(std::exchange(other._root, nullptr))
        , _size(std::exchange(other._root, 0)) {}

    ~bst();

public: // operators
    bst&
    operator=(const bst& other);

    bst&
    operator=(bst&& other);

public: // methods
    std::pair<iterator, bool>
    insert(value_type&& value);

    size_type
    erase(value_type&& key);

    node_type
    extract(value_type&& key);

    void
    clear();

    size_type
    count(const_reference value) const;

    iterator
    find(const_reference key);

    const_iterator
    find(const_reference key) const;

    bool
    contains() const;

    bool
    empty() const;

    iterator
    begin();

    iterator
    end();

    const_iterator
    begin() const;

    const_iterator
    end() const;

    reverse_iterator
    rbegin();

    reverse_iterator
    rend();

    const_reverse_iterator
    rbegin() const;

    const_reverse_iterator
    rend() const;
};

