#include <gtest/gtest.h>

#include "container.hpp"

using namespace std;

auto make_evector(size_t count) -> evector<size_t>;


TEST(reserve, ctor) {
    const size_t count = 10;
    evector<int> ev(count);

    ASSERT_EQ(ev.size(), count);
}

TEST(resize, methods) {
    const size_t count1 = 10;
    const size_t count2 = count1 - 4;

    evector<int> ev;
    ASSERT_EQ(ev.size(), 0);

    ev.resize(count1);
    ASSERT_EQ(ev.size(), count1);

    for (size_t n = 0; n < count1; ++n) {
        ev[n] = n;
    }

    ev.resize(count2);
    ASSERT_EQ(ev.size(), count2);

    for (size_t n = 0; n < count2; ++n) {
        ASSERT_EQ(ev[n], n);
    }
}

TEST(push_back, methods) {
    const size_t count = 10;
    evector<size_t> ev;

    for (size_t n = 0; n < count; ++n) {
        ev.push_back(n);
        ASSERT_EQ(ev.back(), n);
    }

    ASSERT_EQ(ev.size(), count);
}

/* TEST(default, iterator) { */
/*     const size_t count = 10; */
/*     auto ev = make_evector(count); */

/*     size_t item = 0; */
/*     for (auto it = ev.begin(); it != ev.end(); ++it) { */
/*         ASSERT_EQ(*it, item++); */
/*     } */
/* } */


auto main(int argc, char** argv) -> int {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

auto make_evector(size_t count) -> evector<size_t> {
    evector<size_t> ev(count);

    for (size_t n = 0; n < count; ++n) {
        ev.push_back(n);
    }

    return ev;
}

