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

    int n = 0;
    for (const auto& item : tree)
        ASSERT_EQ(item, ++n);
    ASSERT_EQ(n, tree.size());

    for (auto iter = tree.rbegin(); iter != tree.rend(); ++iter)
        ASSERT_EQ(*iter, n--);
    ASSERT_EQ(n, 0);
}

TEST(method, find)
{
    bst<int> tree;
    for (int n = 0; n < 10; n++) {
        tree.insert(n);
        ASSERT_EQ(*tree.find(n), n);
    }
}

TEST(method, erase)
{
    {
        bst<int> tree;
        tree.insert(5);
        tree.insert(4);
        tree.insert(6);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(8);
        tree.insert(1);
        tree.insert(9);
        int old_size = tree.size();

        tree.erase(tree.find(3));
        ASSERT_EQ(old_size, tree.size() + 1);

        int n = 1;
        for (const auto& item : tree) {
            ASSERT_EQ(n++, item);
            if (n == 3)
                n++;
        }
    }
    {
        bst<int> tree;
    
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);
        tree.insert(1);
        tree.insert(9);
        int old_size = tree.size();

        tree.erase(tree.find(3));
        ASSERT_EQ(old_size, tree.size() + 1);

        int n = 1;
        for (const auto& item : tree) {
            ASSERT_EQ(n++, item);
            if (n == 3)
                n++;
        }
    }
}

TEST(method, output)
{
    bst<int> tree;

    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    int n = 1;
    for (const auto& item : tree.output())
        ASSERT_EQ(item, n++);
}


int
main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

