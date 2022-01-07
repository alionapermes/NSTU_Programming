#include <gtest/gtest.h>
#include <stdio.h>

#include "matrix.hpp"


matrix<int> get_matrix(const size_t rows, const size_t cols);


TEST(ostream, operator)
{
    //
}

TEST(compare, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1 = get_matrix(rows, cols);
    const auto m2 = get_matrix(rows, cols);

    ASSERT_TRUE(m1 == m2);
}

TEST(copy, operatror)
{
    auto m1 = get_matrix(2, 3);
    auto m2 = m1;

    ASSERT_TRUE(m1 == m2);
}

TEST(sum, operator) // todo
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1 = get_matrix(rows, cols);
    const auto m2 = get_matrix(rows, cols);

    try {
        const auto m3 = m1 + m2;
        
        ASSERT_EQ(m3.get_rows(), m1.get_rows());
        ASSERT_EQ(m3.get_cols(), m1.get_cols());

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                ASSERT_EQ(m3[row][col], (m1[row][col] + m2[row][col]));
            }
        }
    } catch (std::exception e) {
        printf("error: %s\n", e.what());
    }
}

TEST(default, constructor)
{
    matrix<int> m;

    ASSERT_EQ(m.get_rows(), 0);
    ASSERT_EQ(m.get_cols(), 0);
}

TEST(params, constructor)
{
    const size_t rows = 2;
    const size_t cols = 3;
    matrix<int> m(rows, cols);

    ASSERT_EQ(m.get_rows(), rows);
    ASSERT_EQ(m.get_cols(), cols);
}

TEST(copy, construct)
{
    matrix<int> m1 = get_matrix(2, 3);
    matrix<int> m2(m1);

    ASSERT_TRUE(m1 == m2);
}

TEST(resize, methods)
{
    const size_t old_rows = 3;
    const size_t old_cols = 4;
    const size_t new_rows = 2;
    const size_t new_cols = 5;

    auto test_m = get_matrix(old_rows, old_cols);
    const auto base = get_matrix(old_rows, old_cols);

    test_m.resize(new_rows, new_cols);

    ASSERT_EQ(test_m.get_rows(), new_rows);
    ASSERT_EQ(test_m.get_cols(), new_cols);

    for (size_t row = 0; row < new_rows; row++) {
        for (size_t col = 0; col < new_cols; col++) {
            if ((row < old_rows) && (col < old_cols)) {
                ASSERT_EQ(test_m[row][col], base[row][col]);
            }
        }
    }
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


matrix<int> get_matrix(const size_t rows, const size_t cols)
{
    int counter = 0;
    matrix<int> m(rows, cols);

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            m[row][col] = counter++;
        }
    }

    return m;
}
