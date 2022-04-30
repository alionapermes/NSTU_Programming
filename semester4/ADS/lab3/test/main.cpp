#include "gtest/gtest.h"

#include "two_three_tree.hpp"


TEST(ctor, default)
{
    TwoThreeTree ttt;
    ttt.insert(4);
    ttt.insert(3);
    ttt.insert(5);

    ASSERT_EQ(ttt.get<1>(), 3);
    ASSERT_EQ(ttt.get<2>(), 4);
    ASSERT_EQ(ttt.get<3>(), 5);
}


int
main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

