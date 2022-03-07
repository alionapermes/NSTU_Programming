#include "container.hpp"

#include "gtest/gtest.h"

using namespace std;


list_v3<size_t>
make_list(size_t cap);


TEST(ctor, default)
{
    list_v3<int> l;

    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.capacity(), 0);
}

TEST(operator, index)
{
    list_v3<size_t> l(10);

    for (size_t n = 0; n < l.capacity(); n++) {
        l[n] = n;
        ASSERT_EQ(l[n], n);
    }
}

TEST(operator, copy_assignment)
{
    const list_v3<size_t> list1 = make_list(4);
    const list_v3<size_t> list2 = list1;

    ASSERT_EQ(list1.size(), list2.size());
    ASSERT_EQ(list1.capacity(), list2.capacity());

    for (size_t n = 0; n < list1.size(); n++)
        ASSERT_EQ(list1[n], list2[n]);
}

TEST(method, size)
{
    list_v3<int> l(4);
    ASSERT_EQ(l.size(), 0);

    for (int i = 0; i < 4; i++) {
        l[i] = i;
        ASSERT_EQ(l.size(), i + 1);
    }
}

TEST(method, capacity)
{
    list_v3<int> l(10);
    ASSERT_EQ(l.capacity(), 10);
}

TEST(method, clear)
{
    list_v3<int> l(10);
    l.clear();

    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.capacity(), 0);
}

TEST(method, reserve)
{
    list_v3<size_t> list1 = make_list(4);
    list_v3<size_t> list2 = list1;
    const size_t new_cap  = list1.capacity() * 2;

    list2.reserve(new_cap);
    ASSERT_EQ(list2.capacity(), new_cap);

    for (size_t n = 0; n < list1.size(); n++)
        ASSERT_EQ(list1[n], list2[n]);

    list2.reserve(list2.capacity());
    ASSERT_EQ(list2.capacity(), new_cap);

    list2.reserve(list2.capacity() / 2);
    ASSERT_EQ(list2.capacity(), new_cap);
}

TEST(method, foreach)
{
    list_v3<size_t> l = make_list(4);
    size_t n          = 0;

    for (const auto& item : l)
        ASSERT_EQ(item, n++);

    ASSERT_EQ(l.size(), n);
}

TEST(method, front)
{
    list_v3<size_t> l = make_list(4);
    ASSERT_EQ(l.front(), l[0]);
}

TEST(method, back)
{
    list_v3<size_t> test_l  = make_list(4);
    const size_t last_index = test_l.size() - 1;

    ASSERT_EQ(test_l.back(), test_l[last_index]);
}

TEST(method, push_front)
{
    size_t counter = 0;
    list_v3<size_t> l;
    
    for (; counter < 10; counter++) {
        l.push_front(counter);
        ASSERT_EQ(l.front(), counter);
    }

    ASSERT_EQ(l.size(), counter);
    ASSERT_EQ(l.capacity(), counter);
}

TEST(method, push_back)
{
    size_t counter = 0;
    list_v3<size_t> l;

    for (; counter < 10; counter++) {
        l.push_back(counter);
        ASSERT_EQ(l.back(), counter);
    }

    ASSERT_EQ(l.size(), counter);
    ASSERT_EQ(l.capacity(), counter);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

list_v3<size_t>
make_list(size_t cap)
{
    list_v3<size_t> l(cap);

    for (size_t n = 0; n < cap; n++)
        l[n] = n;

    return l;
}

