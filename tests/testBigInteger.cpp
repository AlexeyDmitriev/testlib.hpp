#include <boost/test/unit_test.hpp>
#include "libs/BigInteger/BigInteger.hpp"
#include "tests/testReadTools.hpp"
#include "testRandomTools.hpp"

BOOST_FIXTURE_TEST_SUITE(BigIntegerStrict, StrictRead)

BOOST_AUTO_TEST_CASE(BigIntegerRead){
	setStr("-894 ");
	BOOST_CHECK_EQUAL(stream.read<BigInteger>().toLong(), -894);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(BigIntegerRandom, RandomTest)

BOOST_AUTO_TEST_CASE(BigIntegerRandom){
	BigInteger from = BigInteger(010100);
	BigInteger to = BigInteger(100100);
	BigInteger r = rnd.next<BigInteger>(from, to);
	BOOST_CHECK(from <= r && r <= to); 
}

BOOST_AUTO_TEST_SUITE_END()
