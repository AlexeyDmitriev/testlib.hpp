#include <boost/test/unit_test.hpp>
#include "libs/BigInteger/BigInteger.hpp"
#include "tests/testReadTools.hpp"
#include "testRandomTools.hpp"

BOOST_FIXTURE_TEST_SUITE(BigIntegerStrict, StrictRead)

BOOST_AUTO_TEST_CASE(BigIntegerRead){
	setStr("-894 ");
	BOOST_CHECK_EQUAL(stream.read<BigInteger>().toInteger(), -894);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(BigIntegerRandom, RandomTest)

BOOST_AUTO_TEST_CASE(BigIntegerRandom){
	BigInteger from = BigInteger(010100);
	BigInteger to = BigInteger(100100);
	BigInteger r = rnd.next<BigInteger>(from, to);
	BOOST_CHECK(from <= r && r <= to);
}

BOOST_AUTO_TEST_CASE(BIgcd) {
	{
		BigInteger a(3);
		BigInteger b(5);
		BOOST_CHECK_EQUAL(gcd(a, b), BigInteger(1));
	}
	{
		BigInteger a("10394540081827693200473815328053988703889568");
		BigInteger b("10008658978277140167971344646087256144407296");
		BOOST_CHECK_EQUAL(gcd(a, b), BigInteger("2669734086172442650208"));
	}
}

BOOST_AUTO_TEST_SUITE_END()
