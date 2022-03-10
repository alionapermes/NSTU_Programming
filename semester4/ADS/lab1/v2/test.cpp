#include "container.hpp"

#include "gtest/gtest.h"
#include "tl/expected.hpp"

using namespace std;

evector<size_t>
make_evector(size_t count);


TEST(operator, index)
{
    evector<size_t> ev(3);

    for (size_t n = 0; n < 3; n++) {
        ev[n] = n;
        ASSERT_EQ(ev[n], n);
    }
}

TEST(method, at)
{
    evector<size_t> ev = make_evector(3);

    for (size_t n = 0; n < 3; n++) {
        auto item = ev.at(n);
        ASSERT_EQ(**item, n);
    }
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

evector<size_t>
make_evector(size_t cap)
{
    evector<size_t> ev(cap);

    for (size_t n = 0; n < cap; ++n) {
        ev[n] = n;
    }

    return ev;
}

