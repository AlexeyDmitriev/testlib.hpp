#include "testTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testlib/verdictFunctions.hpp"
#include "testlib/random.hpp"
#include "testlib/generators/int.hpp"
BOOST_AUTO_TEST_CASE(basicRandom){
	Random rnd(1);

	int value = rnd.next<int>(5, 5);
	BOOST_CHECK_EQUAL(5, value);

	value = rnd.next<int>(5, 10);
	BOOST_CHECK(value >= 5 && value <= 10);
}
