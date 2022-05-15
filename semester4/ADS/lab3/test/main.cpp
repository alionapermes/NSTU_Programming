#include "gtest/gtest.h"

/* #define ITERATIVE */
#define RECURSIVE
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

    ASSERT_EQ(n, ttt.size());

    ttt.erase(ttt.find(3));
    ttt.erase(ttt.find(1));
    ttt.erase(ttt.find(5));
    ttt.erase(ttt.find(4));
    ttt.erase(ttt.find(2));
    ttt.erase(ttt.find(9));
    ttt.erase(ttt.find(10));
    ttt.erase(ttt.find(8));
    ttt.erase(ttt.find(7));
    ttt.erase(ttt.find(6));
    ASSERT_EQ(ttt.size(), 0);
}


int
main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

