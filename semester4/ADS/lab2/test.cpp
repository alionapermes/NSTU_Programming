#include <gtest/gtest.h>
#include "container.hpp"

using namespace std;


TEST(insert, methods)
{
    binary_tree<int> tree;
    tree.insert(4);

    auto it = tree.begin();

    ASSERT_EQ(*it, 4);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

