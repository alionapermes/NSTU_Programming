#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include <variant>
#include <vector>


enum class Type : bool
{ Node, Leaf };

enum class Sprt : bool
{ _1, _2 };

template <typename Key = int, typename Compare = std::less<Key>>
class TwoThreeTree
{
private:
    struct Unit;

public:
    struct Iterator;

public: // typedefs
    using value_type             = Key;
    using unit_type              = Unit;
    using size_type              = size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = Iterator;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
    struct Iterator
    {
        private:
            unit_type* root_;
            unit_type* leaf_;

        public:
            Iterator(unit_type* root, unit_type* leaf)
                : root_(root), leaf_(leaf) {}
    };

private:
    struct Unit
    {
        friend TwoThreeTree;

    private:
        Type type_;
        value_type sprt_1_;
        value_type sprt_2_;
        unit_type* left_  = nullptr;
        unit_type* mid_   = nullptr;
        unit_type* right_ = nullptr;

    public:
        Unit(value_type&& value)
            : type_(Type::Leaf), sprt_1_(std::move(value)) {}

        Unit(value_type&& sprt_1, value_type&& sprt_2)
            : type_(Type::Node)
            , sprt_1_(std::move(sprt_1))
            , sprt_2_(std::move(sprt_2_))
        {}

        Unit(
            unit_type* left,
            unit_type* mid   = nullptr,
            unit_type* right = nullptr
        ) : type_(Type::Node), left_(left), mid_(mid), right_(right) {}

        Unit(
            value_type&& sprt_1,
            value_type&& sprt_2,
            unit_type* left,
            unit_type* mid,
            unit_type* right
        )
            : type_(Type::Node)
            , sprt_1_(std::move(sprt_1))
            , sprt_2_(std::move(sprt_2))
            , left_(left)
            , mid_(mid)
            , right_(right)
        {}

        Type
        type() const
        { return type_; }

        bool
        is_leaf() const
        { return type_ == Type::Leaf; }

        bool
        is_node() const
        { return type_ == Type::Node; }

        template <Sprt Separator = Sprt::_1>
        reference
        get()
        { return (Separator == Sprt::_1 ? sprt_1_ : sprt_2_); }
    };

private:
    size_type size_  = 0;
    unit_type* root_ = nullptr;
    unit_type* base_ = nullptr;

public:
    TwoThreeTree() = default;

    template <size_t Leaf>
    const_reference
    get() const
    {
        if (Leaf == 1)
            return root_->left_->get();
        if (Leaf == 2)
            return root_->mid_->get();
        if (Leaf == 3)
            return root_->right_->get();
    }

    iterator
    insert(value_type&& key)
    { return insert(root_, std::move(key)); }

    iterator
    insert(unit_type*& node, value_type&& key)
    {
        // если контейнер пуст - инициализируем корень
        if (node == nullptr) {
            node = new unit_type(new unit_type(std::move(key)));
            return iterator(root_, node->left_);
        }

        // если свободен средний подузел,
        // то пробуем инициализировать его листом
        if (node->mid_ == nullptr) {
            // если вставляемый ключ больше левого подузла-листа
            if (key > node->left_->get()) {
                // то первый разделитель устанавливается равным ключу
                node->sprt_1_ = key;
                // средний подузел инициализируется листом со значением ключа
                node->mid_    = new unit_type(std::move(key));
                return iterator(root_, node->mid_);
            }
            // иначе, если ключ меньше левого листа
            else if (key < node->left_->get()) {
                // то первый разделитель устанавливается
                // равным значению левого подузла-листа
                node->sprt_1_ = node->left_->get();
                // а сам левый подузел занимает место среднего
                node->mid_    = node->left_;
                // левый подузел инициализируется листом со значением ключа
                node->left_   = new unit_type(std::move(key));
                return iterator(root_, node->left_);
            }
        }
        // если свободен только правый подузел
        else if (node->right_ == nullptr) {
            // если вставляемый ключ маеньше левого подузла-листа
            if (key < node->left_->get()) {
                node->right_  = node->mid_;
                node->sprt_2_ = node->right_->get();
                node->mid_    = node->left_;
                node->sprt_1_ = node->mid_->get();
                node->left_   = new unit_type(std::move(key));
                return iterator(root_, node->left_);
            }
            // если ключ больше левого и меньше среднего подузла-листа
            else if ((node->left_->get() < key) && (key < node->mid_->get())) {
                node->right_  = node->mid_;
                node->sprt_2_ = node->right_->get();
                node->mid_    = new unit_type(std::move(key));
                node->sprt_1_ = node->mid_->get();
                return iterator(root_, node->mid_);
            }
            // если ключ больше значений других подузлов-листьев
            else if (key > node->mid_->get()) {
                node->sprt_2_ = key;
                node->right_  = new unit_type(std::move(key));
                return iterator(root_, node->right_);
            }
        }
        // если свободных подузлов не осталось
        else {
            //
        }
    }

    /* iterator */
    /* insert( */
    /*     unit_type* root, */
    /*     value_type&& key */
    /* ) { */
    /*     if (root->is_leaf()) { */
    /*         if (key == root->get()) */
    /*             return end(); */
            
    /*         node = leaf; */
            
    /*         if (root->get() < leaf->get()) { */
    /*             min_key = leaf->get(); */
    /*         } else { */
    /*             min_key = root->get(); */

    /*             auto temp1 = root->get(); */
    /*             root->get() = leaf->get(); */
    /*             leaf->get() = temp1; */

    /*             /1* auto temp2 = root-> *1/ */
    /*         } */
    /*     } */
    /* } */

    iterator
    end()
    { /**/ }

    /* typename base::iterator */
    /* erase(typename base::iterator pos) override */
    /* {} */

    /* void */
    /* clear() override */
    /* {} */

    /* typename base::iterator */
    /* find(typename base::const_reference key) override */
    /* {} */

    //
};

