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
