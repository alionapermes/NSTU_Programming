#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>


template <typename Value = int>
class htab
{
public:
    struct htab_iterator;

private:
    struct item;

public:
    using value_type      = Value;
    using item_type       = item;
    using size_type       = size_t;
    using reference       = value_type&;
    using pointer         = value_type*;
    using const_reference = const value_type&;
    using const_pointer   = const value_type*;
    using iterator        = htab_iterator;

private:
    enum class item_state : char
    {
        used,
        unused,
        empty
    };

    struct item
    {
    private:
        value_type _value;
        item_state _state = item_state::empty;

    public:
        item() = default;

        item(
            value_type&& value,
            item_state state
        )
            : _value(std::move(value))
            , _state(state)
        {}

        reference
        value()
        { return _value; }

        void
        set(value_type&& value)
        {
            _value = std::move(value);
            _state = item_state::used;
        }

        item_state
        state()
        { return _state; }
    };

public:
    struct htab_iterator
    {
    private:
        item_type* _ptr = nullptr;

    public:
        htab_iterator() = default;

        htab_iterator(item_type* ptr) : _ptr(ptr) {}

        reference
        operator*()
        { return _ptr->value(); }

        pointer
        operator->()
        { return &_ptr->value(); }

        bool
        operator==(const iterator& other)
        { return other._ptr == _ptr; }
    };

private:
    size_type _cap   = 0;
    size_type _size  = 0;
    item_type* _data = nullptr;

public:
    htab(size_type cap) : _cap(cap), _data(new item_type[cap]()) {}

    ~htab()
    { clear(); }

    void
    clear()
    {
        delete[] _data;
        _data = nullptr;
        _size = 0;
    }

    size_type
    size() const
    { return _size; }

    template <typename T>
    iterator
    insert(T&& value)
    {
        if (_data == nullptr)
            _data = new item_type[_cap]();

        iterator iter;

#ifdef LINEAR
        iter = linear_insert(std::forward<value_type>(value));
#elif defined QUADRATIC
        iter = quadratic_insert(std::forward<value_type>(value));
#endif

        if (iter != end())
            ++_size;
        return iter;
    }

    template <typename T>
    void
    erase(T&& value)
    { return erase(find(std::forward<value_type>(value))); }

    void
    erase(iterator pos)
    { pos->set_state(item_state::unused); }

    template <typename T>
    iterator
    find(T&& value)
    {
        size_type index = get_hash(std::forward<value_type>(value));
        return _data[index];
    }

    iterator
    end()
    { return iterator(nullptr); }

private:
    size_type
    get_hash(reference value)
    {
#ifdef MULTIPLICATIVE
        return multiplicative_hashing(value);

#elif defined MUDULE
        uint64_t key;

        if (value > 100'000) {
#ifdef CHOOSING_NUMBER
            key = choosing_number(value);
#elif defined CONVOLUTION
            key = convolution(value);
#endif
        } else
            key = value;

        return module_hashing(key);
#endif
    }

#ifdef LINEAR
    iterator
    linear_insert(value_type&& value, size_type try_n = 0)
    {
        size_type index = get_hash(value) + try_n;

        if (_data[index].state() != item_state::empty)
            return linear_insert(std::move(value), try_n + 1);

        _data[index].set(std::move(value));
        return iterator(_data + index);
    }
#elif defined QUADRATIC
    iterator
    quadratic_insert(value_type&& value, size_t try_n = 0)
    {
        static const int c1 = 3;
        static const int c2 = 8;

        size_type index =
            (get_hash(value) + (c1 * try_n) + (c2 * try_n * try_n)) % _cap;

        if (_data[index].state() != item_state::empty)
            return quadratic_insert(std::move(value), try_n + 1);

        _data[index].set(std::move(value));
        return iterator(_data + index);
    }
#endif

#ifdef CHOOSING_NUMBER
    uint64_t
    choosing_number(uint64_t num)
    {
        int n1 = 0, n2 = 0, n3 = 0;
        
        for (int counter = 0; num > 0; ++counter) {
            int tail = num % 10;

            if (counter < 1)
                n1 += tail;
            else if (counter < 6)
                n2 += tail;
            else
                n3 += tail;

            num /= 10;
        }

        return (((n3 % 10) * 100) + ((n2 % 10) * 10) + (n1 % 10));
    }
#endif

#ifdef CONVOLUTION
    uint64_t
    convolution(uint64_t num)
    {
        std::vector<int> parts;
        int tmp = 0;

        for (int counter = 0; num > 0; ++counter) {
            int tail = num % 10;

            if (counter == 3) {
                parts.push_back(tmp);
                tmp     = 0;
                counter = 0;
            }

            tmp += tail * std::pow(10, counter);
            num /= 10;
        }

        int xor_n = 1;
        for (auto& p : parts)
            tmp += p ^ xor_n++;

        return tmp % 1'000;
    }
#endif

#ifdef MODULE
    size_type
    module_hashing(std::uint64_t key)
    { return (key % _cap); }
#endif

#ifdef MULTIPLICATIVE
    inline float
    fract(float num)
    { return num - static_cast<int>(num); }

    uint64_t
    str_to_natural(std::string_view sw)
    {
        size_type digit = sw.length() - 1;
        uint64_t nat = 0;

        for (auto ltr : sw)
            nat += static_cast<uint64_t>(ltr) * (10 * digit--);
        return nat;
    }

    uint64_t
    multiplicative_hashing(std::string key)
    {
        static const float A = (std::sqrt(5) - 1) / 2;
        return _cap * fract(str_to_natural(key) * A);
    }
#endif
};

