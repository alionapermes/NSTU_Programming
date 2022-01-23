#pragma once

#include <cstddef>
#include <iterator>


template <typename T>
class binary_tree
{
public:
    struct node
    {
    public:
        friend class binary_tree;

        node() {}

        node(const T& _value) : value(_value) {}

        node(const T& _value, node* _left, node* _right)
        : value(_value), left(_left), right(_right) {}

    private:
        T value;
        node* left  = nullptr;
        node* right = nullptr;
    };

    struct btree_iterator
    {
    public:
        friend class binary_tree;

        using iterator_category = std::bidirectional_iterator_tag;
        using iterator          = btree_iterator;
        using difference_type   = ptrdiff_t;
        using value_type        = T;
        using reference         = value_type&;
        using pointer           = value_type*;

        btree_iterator(node* ptr) : m_ptr(ptr) {}

        iterator&
        operator++() // todo
        {
            m_ptr = m_ptr->left;
            return *this;
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
        node* m_ptr = nullptr;
    };

    using value_type             = T;
    using size_type              = std::size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator               = btree_iterator;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    binary_tree() {};
    
    binary_tree(const binary_tree& tree)
    {
        // todo
    }

    ~binary_tree()
    { clear(); delete border; }

    iterator
    begin()
    {
        node* tmp = root;

        while (tmp->left != nullptr) {
            tmp = tmp->left;
        }

        return iterator(tmp);
    }

    iterator
    end()
    { return iterator(border); }

    const_iterator
    begin() const
    { return const_iterator(root); }

    const_iterator
    end() const
    { return const_iterator(border); }

    size_type
    size() const
    { return _size; }

    bool
    empty() const
    { return _size == 0; }

    void
    clear()
    { erase(iterator(root)); }

    iterator
    insert(const_reference value)
    {
        if (root == nullptr) {
            root = new node(value);
            return iterator(root);
        }

        auto it = iterator(root);

        while (true) {
            if (value < *it) {
                if (it.m_ptr->left == nullptr) {
                    it.m_ptr->left = new node(value);
                    ++_size;
                    return iterator(it.m_ptr->left);
                } else {
                    it = iterator(it.m_ptr->left);
                }
            } else {
                if (it.m_ptr->right == nullptr) {
                    it.m_ptr->right = new node(value);
                    ++_size;
                    return iterator(it.m_ptr->right);
                } else {
                    it = iterator(it.m_ptr->right);
                }
            }
        }

        return it;
    }

    iterator
    erase(iterator pos, bool recursive = false)
    {
        // todo
        return pos;
    }

    iterator
    find(iterator pos, const_reference value) const
    {
        if (value == *pos) { return pos; }

        if (value < *pos) {
            return find(iterator(pos.m_ptr->left), value);
        } else {
            return find(iterator(pos.m_ptr->right), value);
        }

        return end();
    }

    iterator
    find(const_reference value) const
    { return find(begin(), value); }

private:
    size_type _size  = 0;
    node*     root   = nullptr;
    node*     border = nullptr;
};

