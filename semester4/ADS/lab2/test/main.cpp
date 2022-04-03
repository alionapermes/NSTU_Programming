#include "gtest/gtest.h"

#include "bst_impl.hpp"


TEST(method, insert)
{
    bst<int> tree;

    ASSERT_EQ(*tree.insert(2), 2);
    ASSERT_EQ(*tree.insert(1), 1);
    ASSERT_EQ(*tree.insert(3), 3);

    ASSERT_EQ(tree.size(),  3);
    ASSERT_EQ(tree.front(), 1);
    ASSERT_EQ(tree.back(),  3);
}

TEST(iterator, forward)
{
    bst<int> tree;

    ASSERT_EQ(*tree.insert(2), 2);
    ASSERT_EQ(*tree.insert(1), 1);
    ASSERT_EQ(*tree.insert(3), 3);

    auto tmp = tree.rbegin();
    ASSERT_EQ(*tmp, tree.back());
    --tmp;
    ASSERT_EQ(*tmp, 2);

    auto tmp2 = tree.begin();
    ++tmp2;
    ASSERT_EQ(*tmp2, 2);
    ASSERT_EQ(*tmp, *tmp2);

    /* int n = 0; */
    /* for (const auto& item : tree) */
    /*     ASSERT_EQ(item, ++n); */
    /* ASSERT_EQ(n, tree.size()); */

    /* for (auto iter = tree.rbegin(); iter != tree.rend(); ++iter) */
    /*     ASSERT_EQ(*iter, --n); */
    /* ASSERT_EQ(n, 0); */
}


int
main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

