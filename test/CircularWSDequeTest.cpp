#define BOOST_TEST_MODULE CircularArrayTests
#include <boost/test/unit_test.hpp>

#include "CircularWSDeque.h"

BOOST_AUTO_TEST_CASE(CircularWSDequeSteal)
{
	CircularWSDeque<int> cwd(64);
	cwd.push_bottom(5);
	BOOST_CHECK_EQUAL(5, cwd.steal());
	BOOST_CHECK_EQUAL(0, cwd.steal());
}

BOOST_AUTO_TEST_CASE(CircularWSDequePop)
{
	CircularWSDeque<int> cwd(64);
	cwd.push_bottom(5);
	BOOST_CHECK_EQUAL(5, cwd.pop_bottom());
	BOOST_CHECK_EQUAL(0, cwd.pop_bottom());
}

BOOST_AUTO_TEST_CASE(CircularWSDequeGrowShrink)
{
	// start with a small log size - array size = 2^1 = 2
	CircularWSDeque<int> cwd(1);

	BOOST_TEST_MESSAGE("size: " << cwd.storage_size());
	BOOST_CHECK_EQUAL(2, cwd.storage_size());

	cwd.push_bottom(1337);
	cwd.push_bottom(1337);
	
	// expect first grow - double from 2 to 4
	BOOST_CHECK_EQUAL(4, cwd.storage_size());

	cwd.push_bottom(1337);
	cwd.push_bottom(1337);

	// next grow - double from 4 to 8
	BOOST_CHECK_EQUAL(8, cwd.storage_size());
	cwd.push_bottom(1337);
	cwd.push_bottom(1337);
	cwd.push_bottom(1337);
	// still checking that it didn't grow
	BOOST_CHECK_EQUAL(8, cwd.storage_size());
	cwd.push_bottom(1337);

	// final grow - exp from 4 to 16
	BOOST_CHECK_EQUAL(16, cwd.storage_size());

	// BOOST_TEST_MESSAGE("size: " << sizeof(cwd));
	BOOST_TEST_MESSAGE("size: " << cwd.storage_size());


	// start popping - expect the first shrink at ~1/K elements i.e. 1/3 i.e. 5 elements
	cwd.pop_bottom(); // 1
	cwd.pop_bottom(); // 2
	BOOST_CHECK_EQUAL(16, cwd.storage_size());
	cwd.pop_bottom(); // 3
	cwd.pop_bottom(); // 4
	cwd.pop_bottom(); // 5 - we hit 1/K, shrinking
	BOOST_CHECK_EQUAL(8, cwd.storage_size());
}
