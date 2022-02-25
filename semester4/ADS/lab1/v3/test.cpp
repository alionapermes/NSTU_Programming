#include "container.hpp"

#include "gtest/gtest.h"

using namespace std;


list_v3<size_t>
make_list(size_t capacity);


TEST(ctor, default)
{
    list_v3<int> l;

    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.capacity(), 0);
}

TEST(ctor, reserve)
{
    list_v3<int> l(10);

    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.capacity(), 10);
}

TEST(methods, reserve)
{
    list_v3<size_t> list1 = make_list(4);
    list_v3<size_t> list2 = list1;
    const size_t new_cap  = list1.capacity() * 2;

    list2.reserve(new_cap);
    ASSERT_EQ(list2.capacity(), new_cap);

    for (size_t n = 0; n < list1.size(); n++) {
        ASSERT_EQ(list1[n], list2[n]);
    }

    list2.reserve(list2.capacity());
    ASSERT_EQ(list2.capacity(), new_cap);

    list2.reserve(list2.capacity() / 2);
    ASSERT_EQ(list2.capacity(), new_cap);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

list_v3<size_t>
make_list(size_t capacity)
{
    list_v3<size_t> l(capacity);

    for (size_t n = 0; n < capacity; n++) {
        /* EXPECT_TRUE(false) << "n: " << n << "\n"; */
        l[n] = n;
    }

    return l;
}

