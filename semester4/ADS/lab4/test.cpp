#include "gtest/gtest.h"


/* #define CONVOLUTION */
/* #define CHOOSING_NUMBER */
#define HORNER

/* #define MODULE */
#define MULTIPLICATIVE

/* #define LINEAR */
#define QUADRATIC

#include "container.hpp"


TEST(method, insert)
{
#ifdef MULTIPLICATIVE
    htab<std::string> ht(100);

    std::string s1 = "onetwo";
    std::string s2 = "abobus";
    std::string s3 = "twoone";
    std::string s4 = "one";
    std::string s5 = "two";

    ht.insert(s1);
    ASSERT_EQ(*ht.find(s1), s1);
    ASSERT_EQ(ht.size(), 1);

    ht.insert(s2);
    ASSERT_EQ(*ht.find(s2), s2);
    ASSERT_EQ(ht.size(), 2);

    ht.insert(s3);
    ASSERT_EQ(*ht.find(s3), s3);
    ASSERT_EQ(ht.size(), 3);

    ht.insert(s4);
    ASSERT_EQ(*ht.find(s4), s4);
    ASSERT_EQ(ht.size(), 4);

    ht.insert(s5);
    ASSERT_EQ(*ht.find(s5), s5);
    ASSERT_EQ(ht.size(), 5);

    ht.size();

#else
    htab<uint64_t> ht(100);

    uint64_t a = 123342954451;
    ht.insert(a);
    ASSERT_EQ(*ht.find(a), a);
    ASSERT_EQ(ht.size(), 1);

    uint64_t b = 123342451954;
    ht.insert(b);
    ASSERT_EQ(*ht.find(b), b);
    ASSERT_EQ(ht.size(), 2);
#endif
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

