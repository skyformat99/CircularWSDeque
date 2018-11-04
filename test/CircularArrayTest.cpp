#define BOOST_TEST_MODULE CircularArrayTests
#include <boost/test/unit_test.hpp>

#include "CircularArray.h"

BOOST_AUTO_TEST_CASE(CircularArrayBadLength)
{
	BOOST_CHECK_THROW( CircularArray<int> c = CircularArray<int>(-1), std::bad_alloc );
}

BOOST_AUTO_TEST_CASE(CircularArrayPutGet)
{
	CircularArray<int> c = CircularArray<int>(10);
	c.put(9, 5);
	BOOST_CHECK_EQUAL(c[9], 5);
}

BOOST_AUTO_TEST_CASE(CircularArrayPutOutOfBounds)
{
	CircularArray<int> c = CircularArray<int>(1);
	c.put(3, 5);
	BOOST_CHECK_EQUAL(c[3], 5);
}

BOOST_AUTO_TEST_CASE(CircularArrayGetOutOfBounds)
{
	CircularArray<int> c = CircularArray<int>(1);
	BOOST_CHECK_EQUAL(c[1341], 0);
}

BOOST_AUTO_TEST_CASE(CircularArrayGrowsSelf)
{
	CircularArray<int> c(1);
	c.put(0, 10);
	c.put(1, 13);
	BOOST_CHECK_EQUAL(c[0], 10);
	BOOST_CHECK_EQUAL(c[1], 13);
	BOOST_CHECK_EQUAL(c.size(), 2);
	BOOST_TEST_MESSAGE("c's old size: " << c.size());
	c = c.grow_self(2, 0);
	BOOST_TEST_MESSAGE("c's new size: " << c.size());
	int successes = 0;
	for (int i = 0; i < c.size(); ++i) {
		if (c[i] == 10 || c[i] == 13) {
			successes += 1;
		}
	}
	BOOST_CHECK_EQUAL(c.size(), 4);
	BOOST_CHECK_EQUAL(successes, 2);
}

BOOST_AUTO_TEST_CASE(CircularArrayGrowsNew)
{
	CircularArray<int> c(1);
	c.put(0, 10);
	c.put(1, 13);
	BOOST_CHECK_EQUAL(c[0], 10);
	BOOST_CHECK_EQUAL(c[1], 13);
	BOOST_CHECK_EQUAL(c.size(), 2);
	BOOST_TEST_MESSAGE("c's old size: " << c.size());
	auto a = c.grow_new(2, 0);
	BOOST_TEST_MESSAGE("a's new size: " << a.size());
	int successes = 0;
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] == 10 || a[i] == 13) {
			successes += 1;
		}
	}
	BOOST_CHECK_EQUAL(a.size(), 4);
	BOOST_CHECK_EQUAL(successes, 2);
}

BOOST_AUTO_TEST_CASE(CircularArrayGrowsNewReplace)
{
	CircularArray<int> c(1);
	c.put(0, 10);
	c.put(1, 13);
	BOOST_CHECK_EQUAL(c[0], 10);
	BOOST_CHECK_EQUAL(c[1], 13);
	BOOST_CHECK_EQUAL(c.size(), 2);
	BOOST_TEST_MESSAGE("c's old size: " << c.size());
	c = c.grow_new(2, 0);
	BOOST_TEST_MESSAGE("c's new size: " << c.size());
	int successes = 0;
	for (int i = 0; i < c.size(); ++i) {
		if (c[i] == 10 || c[i] == 13) {
			successes += 1;
		}
	}
	BOOST_CHECK_EQUAL(c.size(), 4);
	BOOST_CHECK_EQUAL(successes, 2);
}

BOOST_AUTO_TEST_CASE(CircularArrayShrinks)
{
	CircularArray<int> c(8);
	c.put(0, 10);
	c.put(1, 13);
	BOOST_CHECK_EQUAL(c[0], 10);
	BOOST_CHECK_EQUAL(c[1], 13);
	BOOST_CHECK_EQUAL(c.size(), 256); // 2^8
	BOOST_TEST_MESSAGE("c's old size: " << c.size());
	c = c.shrink_self(2, 0);
	BOOST_TEST_MESSAGE("c's new size: " << c.size());
	int successes = 0;
	for (int i = 0; i < c.size(); ++i) {
		if (c[i] == 10 || c[i] == 13) {
			successes += 1;
		}
	}
	BOOST_CHECK_EQUAL(c.size(), 128); // 2^7
	BOOST_CHECK_EQUAL(successes, 2);
}
