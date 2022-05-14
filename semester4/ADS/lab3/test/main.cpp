#include "gtest/gtest.h"

#include "t234.hpp"


TEST(insert, default)
{
    t234 ttt;
    ttt.insert(3);
    ttt.insert(1);
    ttt.insert(5);
    ttt.insert(4);
    ttt.insert(2);
    ttt.insert(9);
    ttt.insert(10);
    ttt.insert(8);
    ttt.insert(7);
    ttt.insert(6);

    int n = 0;
    for (auto item : ttt)
        ASSERT_EQ(item, ++n);

    ASSERT_EQ(n, 10);
}


int
main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

