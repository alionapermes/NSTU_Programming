#include <gtest/gtest.h>
#include <string>

#include "container.hpp"

using namespace std;


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

TEST(size, methods)
{
	const size_t items_count = 10;
	
	bidir_list<size_t> list;
	for (size_t n = 0; n < items_count; n++) {
		list.push_back(n);
	}

	ASSERT_EQ(list.size(), items_count);
}

TEST(forward, iterators)
{
	const size_t items_count = 10;
	size_t value = 0;

	bidir_list<size_t> list;
	for (size_t n = 0; n < items_count; n++) {
		list.push_back(n);
	}

	for (auto it = list.begin(); it != list.end(); it++) {
		ASSERT_EQ(*it, value++);
	}

    ASSERT_EQ(value, items_count);
}

TEST(reverse, iterators)
{
	const size_t items_count = 10;
	size_t value = items_count;

	bidir_list<size_t> list;
	for (size_t n = 0; n < items_count; n++) {
		list.push_back(n);
	}

	for (auto rit = list.rbegin(); rit != list.rend(); rit++) {
		ASSERT_EQ(*rit, --value);
	}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

