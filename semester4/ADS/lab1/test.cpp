#include <gtest/gtest.h>

#include "container.hpp"

using namespace std;


bidir_list<size_t>
make_list(const size_t size);

TEST(copy, ctor)
{
    const size_t items_count = 10;
    auto list1 = make_list(items_count);

    bidir_list<size_t> list2(list1);
    ASSERT_EQ(list1.size(), list2.size());

    for (size_t n = 0; n < items_count; n++) {
        ASSERT_EQ(list1[n], list2[n]);
    }
}

TEST(init_list, ctor)
{
    const size_t items_count = 4;
    auto list    = {0, 1, 2, 3};
    size_t value = 0;

    for (auto it = list.begin(); it != list.end(); it++) {
        ASSERT_EQ(*it, value++);
    }

    ASSERT_EQ(list.size(), value);
}

TEST(push_front, methods)
{
	const size_t items_count = 10;

	bidir_list<size_t> list;
	for (size_t n = 0; n < items_count; n++) {
		list.push_front(n);
		ASSERT_EQ(list.front(), n);
	}
}

TEST(push_back, methods)
{
	const size_t items_count = 10;

	bidir_list<size_t> list;
	for (size_t n = 0; n < items_count; n++) {
		list.push_back(n);
		ASSERT_EQ(list.back(), n);
	}
}

TEST(pop_front, methods)
{
    const size_t items_count = 10;

    auto list = make_list(items_count);
    for (size_t n = 0; n < items_count; n++) {
        list.pop_front();

        if (list.size() > 0) {
            ASSERT_EQ(list.front(), n + 1);
        }
    }
    ASSERT_EQ(list.size(), 0);
}

TEST(pop_back, methods)
{
    const size_t items_count = 10;

    auto list = make_list(items_count);
    for (size_t n = 0; n < items_count; n++) {
        list.pop_back();

        if (list.size() > 0) {
            ASSERT_EQ(list.back(), items_count - n - 2);
        }
    }
    ASSERT_EQ(list.size(), 0);
}

TEST(size, methods)
{
	const size_t items_count = 10;
    const auto list = make_list(items_count);	

	ASSERT_EQ(list.size(), items_count);
}

TEST(clear, methods)
{
    const size_t items_count = 10;

    auto list = make_list(items_count);
    ASSERT_EQ(items_count, list.size());

    list.clear();
    ASSERT_EQ(0, list.size());
}

TEST(find, methods)
{
    const size_t items_count = 10;
    
    auto list = make_list(items_count);
    
    for (auto it = list.begin(); it != list.end(); it++) {
        auto target = list.find(list.begin(), list.end(), *it);
        ASSERT_EQ(*target, *it);
    }
}

TEST(insert, methods)
{
    size_t items_count = 10;
    bidir_list<size_t> list1 = {1, 2, 3, 4};
    bidir_list<size_t> list2 = {1, 2, 5, 3, 4};
    bidir_list<size_t> list3;

    auto it = list1.find(3);
    list1.insert(it, 5);

    ASSERT_EQ(list1.size(), list2.size());
    ASSERT_EQ(list1, list2);

    for (size_t n = 0; n < items_count; n++) {
        list3.insert(list3.end(), n);
        ASSERT_EQ(list3.back(), n);
        ASSERT_EQ(list3.size(), n + 1);
    }
}

TEST(erase, methods)
{
    const size_t items_count = 10;
    
    auto list1 = make_list(items_count);
    for (int n = 0; n < items_count; n++) {
        auto next = list1.erase(n);
        ASSERT_EQ(next, (
            list1.size() == 0
            ? list1.end()
            : list1.begin()
        ));
    }
    ASSERT_EQ(list1.size(), 0);

    auto list2 = make_list(items_count);
    for (int n = items_count - 1; n >= 0; n--) {
        auto next = list2.erase(n);
        ASSERT_EQ(next, list2.end());
    }
    ASSERT_EQ(list2.size(), 0);

    bidir_list<size_t> list3 = {1, 2, 3};
    list3.erase(2);
    ASSERT_EQ(list3.find(2), list3.end());
    ASSERT_EQ(list3.size(), 2);
}

TEST(forward, iterators)
{
	const size_t items_count = 10;
    auto list    = make_list(items_count);
	size_t value = 0;

	for (auto it = list.begin(); it != list.end(); it++) {
		ASSERT_EQ(*it, value++);
	}

    ASSERT_EQ(value, items_count);
}

TEST(reverse, iterators)
{
	const size_t items_count = 10;
    auto list    = make_list(items_count);
	size_t value = items_count;

	for (auto rit = list.rbegin(); rit != list.rend(); rit++) {
		ASSERT_EQ(*rit, --value);
	}
}

TEST(index_write, operator)
{
    const size_t items_count = 10;
    auto list = make_list(items_count);

    for (size_t n = 0; n < list.size(); n++) {
        list[n] = 0;
    }

    for (auto it = list.begin(); it != list.end(); it++) {
        ASSERT_EQ(*it, 0);
    }
}

TEST(index_read, operator)
{
    const size_t items_count = 10;
    size_t value = 0;

    auto list = make_list(items_count);
    for (size_t n = 0; n < list.size(); n++) {
        ASSERT_EQ(list[n], value++);
    }
}

TEST(copy, operator)
{
    const size_t items_count = 10;
    auto list1 = make_list(items_count);
    auto list2 = list1;

    ASSERT_EQ(list1.size(), list2.size());

    for (size_t n = 0; n < items_count; n++) {
        ASSERT_EQ(list1[n], list2[n]);
    }

    list1.clear();
    for (size_t n = 0; n < items_count; n++) {
        ASSERT_EQ(list2[n], n);
    }
}

TEST(compare, operator)
{
    const size_t items_count = 10;
    auto list1 = make_list(items_count);
    auto list2 = make_list(items_count);
    auto list3 = make_list(items_count);

    list3[0] = list3[1];
    ASSERT_EQ(list1, list2);
    ASSERT_NE(list2, list3);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

bidir_list<size_t>
make_list(const size_t size)
{
	bidir_list<size_t> list;
	for (size_t n = 0; n < size; n++) {
		list.push_back(n);
	}

    return list;
}

