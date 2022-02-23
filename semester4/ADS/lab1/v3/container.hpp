// Вариант 3 - односвязная структура данных
// на базе массива с индексными указателями

#pragma once

#include <cstddef>
#include <iterator>

#include "tl/expected.hpp"


template<typename T>
class list_v3
{
public:
    list_v3() = default;

    ~list_v3() = default;

private:
    T** head     = nullptr;
    T** tail     = nullptr;
    T** pointers = nullptr;
};

