#include "gtest/gtest.h"

#define RECURSIVE
#include "randtree.hpp"


TEST(method, insert)
{
    randtree<int> rt;
    
    int item = 0;
    while (item < 10)
        ASSERT_EQ(*rt.insert(++item), item);

    ASSERT_EQ(rt.size(), item);

    item = 0;
    for (int n : rt)
        ASSERT_EQ(n, ++item);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

