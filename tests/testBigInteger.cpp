#include <boost/test/unit_test.hpp>
#include "libs/BigInteger/BigInteger.hpp"
#include "tests/testReadTools.hpp"
#include "testRandomTools.hpp"
#include "testlib/utility.hpp"
#include <vector>
#include <string>

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

BOOST_AUTO_TEST_CASE(arithm) {
	for(int i = -113; i < 113; i += 3) {
		for (int j = -215; j < 215; j += 2) {
			BOOST_CHECK_EQUAL((BigInteger(i) + BigInteger(j)).toString(), toString(i + j));
			BOOST_CHECK_EQUAL((BigInteger(i) - BigInteger(j)).toString(), toString(i - j));
			BOOST_CHECK_EQUAL((BigInteger(i) * BigInteger(j)).toString(), toString(i * j));
			BOOST_CHECK_EQUAL((BigInteger(i) / BigInteger(j)).toString(), toString(i / j));
			BOOST_CHECK_EQUAL((BigInteger(i) % BigInteger(j)).toString(), toString(i % j));
			BOOST_CHECK_EQUAL(gcd(BigInteger(i), BigInteger(j)), BigInteger(std::__gcd(i, j)).abs());
		}
	}
}

BOOST_AUTO_TEST_CASE(zeroOperations) {
	std::vector<std::string> arr = {"47743248374387483247832", "-47743248374387483247832", "0"};
	for (auto s  : arr){
		BigInteger a(s);
		BOOST_CHECK_EQUAL(a + BigInteger::zero(), a);
		BOOST_CHECK_EQUAL(a - BigInteger::zero(), a);
		BOOST_CHECK_EQUAL(BigInteger::zero() + a, a);
		BOOST_CHECK_EQUAL(BigInteger::zero() - a, -a);
		BOOST_CHECK_EQUAL(a * BigInteger::zero(), BigInteger::zero());
		BOOST_CHECK_EQUAL(BigInteger::zero() * a, BigInteger("0"));
		BOOST_CHECK_EQUAL(pow(a, 0), BigInteger::one());
		BOOST_CHECK_EQUAL(gcd(a, BigInteger(0)), a.abs());
		BOOST_CHECK_EQUAL(gcd(BigInteger(0), a), a.abs());
		
		BOOST_CHECK_THROW(a / BigInteger::zero(), VerdictException);
		BOOST_CHECK_THROW(a % BigInteger::zero(), VerdictException);
	}
}
BOOST_AUTO_TEST_SUITE_END()
