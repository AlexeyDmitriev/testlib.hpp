#include <boost/test/unit_test.hpp>
#include "libs/BigInteger/BigInteger.hpp"
#include "tests/testReadTools.hpp"
#include "testRandomTools.hpp"

using namespace biginteger;
BOOST_FIXTURE_TEST_SUITE(BigIntegerStrict, StrictRead)

BOOST_AUTO_TEST_CASE(BigIntegerRead){ //how to use old tests for int?
	setStr("-894 ");
	BOOST_CHECK_EQUAL(stream.read<BigInteger>().toLong(), -894);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(BigIntegerRandom, RandomTest)

BOOST_AUTO_TEST_SUITE_END()
