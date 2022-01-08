#include <gtest/gtest.h>
#include <stdio.h>

#include "matrix.hpp"

using Type = int;

matrix<Type> get_matrix(const size_t rows, const size_t cols);


TEST(compare, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1 = get_matrix(rows, cols);
    const auto m2 = get_matrix(rows, cols);

    ASSERT_TRUE(m1 == m2);
}

TEST(compare2, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1 = get_matrix(rows, cols);
    const auto m2 = get_matrix(rows, cols);

    ASSERT_FALSE(m1 != m2);
}

TEST(copy_m, operatror)
{
    auto m1 = get_matrix(2, 3);
    auto m2 = m1;

    ASSERT_TRUE(m1 == m2);
}

TEST(sum_set, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    auto test_m  = get_matrix(rows, cols);
    const auto m = get_matrix(rows, cols);
    const auto test_m_base = test_m;

    try {
        test_m += m;

        ASSERT_EQ(test_m.get_rows(), rows);
        ASSERT_EQ(test_m.get_cols(), cols);

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                ASSERT_EQ(
                    test_m[row][col],
                    test_m_base[row][col] + m[row][col]
                );
            }
        }
    } catch (const exception& e) {
        printf("error: %s\n", e.what());
    }
}

TEST(dif_set, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    auto test_m  = get_matrix(rows, cols);
    const auto m = get_matrix(rows, cols);
    const auto test_m_base = test_m;

    try {
        test_m -= m;

        ASSERT_EQ(test_m.get_rows(), rows);
        ASSERT_EQ(test_m.get_cols(), cols);

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                ASSERT_EQ(
                    test_m[row][col],
                    test_m_base[row][col] - m[row][col]
                );
            }
        }
    } catch (const exception& e) {
        printf("error: %s\n", e.what());
    }
}

TEST(prod_set, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    auto test_m = get_matrix(rows, cols);
    const auto test_m_base = test_m;
    const Type val = 3;

    test_m *= val;

    ASSERT_EQ(test_m.get_rows(), rows);
    ASSERT_EQ(test_m.get_cols(), cols);

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            ASSERT_EQ(
                test_m[row][col],
                test_m_base[row][col] * val
            );
        }
    }
}

TEST(div_set, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    auto test_m = get_matrix(rows, cols);
    const auto test_m_base = test_m;
    const Type val = 3;

    test_m /= val;

    ASSERT_EQ(test_m.get_rows(), rows);
    ASSERT_EQ(test_m.get_cols(), cols);

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            ASSERT_EQ(
                test_m[row][col],
                test_m_base[row][col] / val
            );
        }
    }
}

TEST(prod, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1     = get_matrix(rows, cols);
    const Type val    = 3;

    const auto m2 = m1 * val;

    ASSERT_EQ(m2.get_rows(), m1.get_rows());
    ASSERT_EQ(m2.get_cols(), m1.get_cols());

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            ASSERT_EQ(
                m2[row][col],
                m1[row][col] * val
            );
        }
    }
}

TEST(div, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1     = get_matrix(rows, cols);
    const Type val    = 3;

    const auto m2 = m1 / val;

    ASSERT_EQ(m2.get_rows(), m1.get_rows());
    ASSERT_EQ(m2.get_cols(), m1.get_cols());

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            ASSERT_EQ(
                m2[row][col],
                m1[row][col] / val
            );
        }
    }
}

TEST(sum, operator)
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

TEST(dif, operator)
{
    const size_t rows = 2;
    const size_t cols = 3;
    const auto m1 = get_matrix(rows, cols);
    const auto m2 = get_matrix(rows, cols);

    try {
        const auto m3 = m1 - m2;
        
        ASSERT_EQ(m3.get_rows(), m1.get_rows());
        ASSERT_EQ(m3.get_cols(), m1.get_cols());

        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                ASSERT_EQ(m3[row][col], (m1[row][col] - m2[row][col]));
            }
        }
    } catch (std::exception e) {
        printf("error: %s\n", e.what());
    }
}

TEST(lt_gt, operator)
{
    matrix<Type> m1 = {{1, 1}, {1, 1}};
    matrix<Type> m2 = {{2, 2}, {2, 2}};

    ASSERT_LT(m1, m2);
    ASSERT_GT(m2, m1);
}

TEST(le_ge, operator)
{
    matrix<Type> m1 = {{2, 2}, {2, 2}};
    matrix<Type> m2 = {{2, 2}, {2, 2}};

    ASSERT_LE(m1, m2);
    ASSERT_GE(m1, m2);
    ASSERT_LE(m2, m1);
    ASSERT_GE(m2, m1);
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

TEST(init_list, constructor)
{
    matrix<Type> m1 = get_matrix(2, 3);
    matrix<Type> m2 = {
        {0, 1, 2},
        {3, 4, 5}
    };

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

TEST(transpose, methods)
{
    matrix<Type> test_m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    const matrix<Type> transposed = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };

    test_m.transpose();

    ASSERT_EQ(test_m, transposed);
}

TEST(to_str, methods)
{
    //
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
