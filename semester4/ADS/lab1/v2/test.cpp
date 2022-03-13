#include "container.hpp"

#include "gtest/gtest.h"
#include "tl/expected.hpp"

#include <string>

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

TEST(operator, move_assignment)
{
    evector<size_t> ev1   = make_evector(3);
    const size_t ev1_cap  = ev1.capacity();
    const size_t ev1_size = ev1.size();

    evector<size_t> ev2 = std::move(ev1);
    ASSERT_EQ(ev2.size(), ev1_size);
    ASSERT_EQ(ev2.capacity(), ev1_cap);

    ASSERT_EQ(ev1.size(), 0);
    ASSERT_EQ(ev1.capacity(), 0);

    for (size_t n = 0; n < ev2.size(); n++)
        ASSERT_EQ(ev2[n], n);
}

TEST(operator, copy_assignment)
{
    evector<size_t> ev1;

    {
        evector<size_t> ev2 = make_evector(3);
        ev1 = ev2;

        ASSERT_EQ(ev1.size(), ev2.size());
        ASSERT_EQ(ev1.capacity(), ev1.capacity());
    }

    for (size_t n = 0; n < ev1.size(); n++)
        ASSERT_EQ(ev1[n], n);
}

TEST(iterator, begin_end)
{
    evector<size_t> ev = make_evector(4);
    auto iter          = ev.begin();

    for (size_t n = 0; n < ev.size(); n++) {
        ASSERT_EQ(*iter, n);
        iter++;
    }

    ASSERT_EQ(iter, ev.end());
}

TEST(iterator, rbegin_rend)
{
    size_t item        = 3;
    evector<size_t> ev = make_evector(item + 1);

    for (auto ritem = ev.rbegin(); ritem != ev.rend(); ++ritem)
        ASSERT_EQ(*ritem, item--);
}

TEST(iterator, math)
{
    evector<size_t> ev = make_evector(4);
    auto iter_last     = ev.begin() + ev.size() - 1;
    auto iter_first    = ev.end() - ev.size();
    
    ASSERT_EQ(*iter_last, ev.back());
    ASSERT_EQ(*iter_first, ev.front());
}

TEST(method, size)
{
    for (size_t n = 1; n <= 10; n++) {
        evector<size_t> ev = make_evector(n);
        ASSERT_EQ(ev.size(), n);
    }
}

TEST(method, capacity)
{
    for (size_t n = 1; n <= 10; n++) {
        evector<size_t> ev = make_evector(n);
        ASSERT_EQ(ev.capacity(), n);
    }
}

TEST(method, clear)
{
    evector<size_t> ev = make_evector(3);
    const size_t cap   = ev.capacity();

    ev.clear();
    ASSERT_EQ(ev.size(), 0);
    ASSERT_EQ(ev.capacity(), cap);
}

TEST(method, at)
{
    evector<size_t> ev = make_evector(3);

    for (size_t n = 0; n < 3; n++) {
        auto item_ptr = *ev.at(n);
        ASSERT_EQ(*item_ptr, n);
    }

    auto item = ev.at(ev.capacity() + 1);
    ASSERT_FALSE(item);
}

TEST(method, front_back)
{
    evector<size_t> ev = make_evector(3);
    ASSERT_EQ(ev.front(), ev[0]);
    ASSERT_EQ(ev.back(), ev[ev.size() - 1]);
}

TEST(method, reserve)
{
    evector<size_t> ev;

    for (size_t n = 1; n < 10; n++) {
        ev.reserve(n);
        ASSERT_EQ(ev.size(), 0);
        ASSERT_EQ(ev.capacity(), n);
    }

    const size_t cap = ev.capacity();

    ev.reserve(3);
    ASSERT_NE(cap, 3);
}

TEST(method, shrink_to_fit)
{
    evector<size_t> ev = make_evector(5);

    ev.pop_front();
    ev.shrink_to_fit();
    ASSERT_EQ(ev.size(), ev.capacity());

    for (size_t n = 0; n < ev.size(); n++)
        ASSERT_EQ(ev[n], n + 1);
}

TEST(method, push_back)
{
    evector<size_t> ev;
    ev.reserve(4);

    size_t n = 0;
    for (; n < 4; n++) {
        ev.push_back(n);
        ASSERT_EQ(ev.back(), n);
        ASSERT_EQ(ev.size(), n + 1);
        ASSERT_EQ(ev.capacity(), 4);
    }

    for (size_t x = 0; x < ev.size(); x++)
        ASSERT_EQ(ev[x], x);

    const size_t old_cap = ev.capacity();

    ev.push_back(ev.size());
    ASSERT_EQ(ev.size(), n+ 1);
    ASSERT_EQ(ev.capacity(), old_cap << 1);

    {
        string base = "something";
        string str(base);
        ASSERT_STREQ(base.c_str(), str.c_str());

        evector<string> evs;
        evs.push_back(std::move(str));

        ASSERT_STRNE(base.c_str(), str.c_str());
        ASSERT_TRUE(str.empty());
    }
}

TEST(method, push_front)
{
    evector<size_t> ev;
    ev.reserve(4);

    size_t n = 0;
    for (; n < 4; n++) {
        ev.push_front(n);
        ASSERT_EQ(ev.front(), n);
        ASSERT_EQ(ev.size(), n + 1);
        ASSERT_EQ(ev.capacity(), 4);
    }

    for (size_t x = 0; x < ev.size(); x++) {
        size_t item = ev.size() - x - 1;
        ASSERT_EQ(ev[x], item);
    }

    const size_t old_cap = ev.capacity();

    ev.push_front(ev.size());
    ASSERT_EQ(ev.size(), n+ 1);
    ASSERT_EQ(ev.capacity(), old_cap << 1);

    {
        string base = "something";
        string str(base);
        ASSERT_STREQ(base.c_str(), str.c_str());

        evector<string> evs;
        evs.push_front(std::move(str));

        ASSERT_STRNE(base.c_str(), str.c_str());
        ASSERT_TRUE(str.empty());
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
    for (size_t n = 0; n < cap; ++n)
        ev[n] = n;

    return ev;
}

