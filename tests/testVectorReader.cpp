#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/vector.hpp"
#include "testTools.hpp"
#include "testlib/readerWrapper.hpp"
#include <vector>
using std::vector;

typedef vector<int> vi;

BOOST_FIXTURE_TEST_SUITE(Vector, NonStrictRead)


BOOST_AUTO_TEST_CASE(testRandom){
	Separator sepTab("\t");
	Separator sepSpace(" ");
	
	
	setStr("2 12 -1");
	vi res = {12, -1};
	BOOST_CHECK(stream.read<vi>() == res);
	setStr("2vs12 -1");
	BOOST_CHECK_THROW(stream.read<vi>(), ReadingException);

	setStr("2\t12 -1");
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace) == res);
	setStr("2\n12 -1");
	BOOST_CHECK_THROW(stream.read<vi>(sepTab, sepSpace), ReadingException);
	
	setStr("3 12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(DefaultReader<int>()) == res);
	setStr("3 12 10teorver1");
	BOOST_CHECK_THROW(stream.read<vi>(DefaultReader<int>()), ReadingException);
	
	
	setStr("3\t12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace, DefaultReader<int>()) == res);
	setStr("3\n12 10 1");
	BOOST_CHECK_THROW(stream.read<vi>(sepTab, sepSpace, DefaultReader<int>()), ReadingException);
	
	setStr("12 10\t\n1");
	res = {12, 10, 1};
	size_t q = 3;
	BOOST_CHECK(stream.read<vi>(q) == res);
	setStr("12 10 1k");
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(q), ReadingException);
	
	setStr("12 \t 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(3, sepSpace) == res);
	setStr("12\t10 1");
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(3, sepSpace), ReadingException);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((unsigned int)(3), DefaultReader<int>()) == res);
	setStr("p12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(q, DefaultReader<int>()), ReadingException);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((long long)(3), sepSpace, DefaultReader<int>()) == res);
	setStr("12 10\n1");
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>((long long)(3), sepSpace, DefaultReader<int>()), ReadingException);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(3, sepSpace) == res);
	setStr("12 10\t1");
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(3, sepSpace), ReadingException);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(StrictVector, StrictRead)

BOOST_AUTO_TEST_CASE(testRandom){
	setStr("2 12 -1");
	vi res = {12, -1};
	BOOST_CHECK_THROW(stream.read<vi>(), ReadingException);
	
	setStr("2\t12 -1");
	res = {12, -1};
	Separator sepTab("\t");
	Separator sep2(" ");
	BOOST_CHECK(stream.read<vi>(sepTab, sep2) == res);
	
	setStr("3 12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(DefaultReader<int>()), ReadingException);
	
	setStr("3\t12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(sepTab, sep2, DefaultReader<int>()) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	size_t q = 3;
	BOOST_CHECK(stream.read<vi>(q) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(q, DefaultReader<int>()) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(q, sep2, DefaultReader<int>()) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(q, sep2) == res);
	
}

BOOST_AUTO_TEST_SUITE_END()

