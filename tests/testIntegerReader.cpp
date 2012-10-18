#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "tests/fixture.hpp"
#include "testlib/testlib.hpp"


BOOST_FIXTURE_TEST_SUITE(Integers, StrictRead)

BOOST_AUTO_TEST_CASE(RandomInts) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<int>(), 42);
	BOOST_CHECK_THROW(stream.read<int>(), ReadingException);

	setStr("-123 999");
	BOOST_CHECK_EQUAL(stream.read<int>(), -123);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<int>(), 999);
}


BOOST_AUTO_TEST_CASE(Negative) {
	setStr("-517");
	BOOST_CHECK_EQUAL(stream.read<int>(), -517);
	
	setStr("-1");
	BOOST_CHECK_EQUAL(stream.read<int>(), -1);
	
	setStr("-1");
	BOOST_CHECK_THROW(stream.read<unsigned>(), ReadingException);
}


BOOST_AUTO_TEST_CASE(Overflow){
	setStr("65535 65535");
	BOOST_CHECK_EQUAL(stream.read<int>(), 65535);
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<short>(), ReadingException);
	
	setStr("9999999999999999999999999999999999999");
	BOOST_CHECK_THROW(stream.read<int>(), ReadingException);
	
	setStr("2000000000");
	BOOST_CHECK_NO_THROW(stream.read<int>());
}

BOOST_AUTO_TEST_CASE(Corners){
	setStr("65535");
	BOOST_CHECK_NO_THROW(stream.read<unsigned short>());
	
	setStr("65536");
	BOOST_CHECK_THROW(stream.read<unsigned short>(), ReadingException);
	
	setStr("-1");
	BOOST_CHECK_THROW(stream.read<unsigned short>(), ReadingException);
	
	
	setStr("32768");
	BOOST_CHECK_THROW(stream.read<short>(), ReadingException);
	
	setStr("-32768");
	BOOST_CHECK_NO_THROW(stream.read<short>());
	
	setStr("-32769");
	BOOST_CHECK_THROW(stream.read<short>(), ReadingException);
	
	
	setStr("18446744073709551616");
	BOOST_CHECK_THROW(stream.read<unsigned long long>(), ReadingException);
	
	setStr("18446744073709551615");
	BOOST_CHECK_NO_THROW(stream.read<unsigned long long>());
	
	
	setStr("9223372036854775808");
	BOOST_CHECK_THROW(stream.read<long long>(), ReadingException);
	
	setStr("9223372036854775807");
	BOOST_CHECK_NO_THROW(stream.read<long long>());
	
	setStr("-9223372036854775809");
	BOOST_CHECK_THROW(stream.read<long long>(), ReadingException);
	
	setStr("-9223372036854775808");
	BOOST_CHECK_NO_THROW(stream.read<long long>());
}

BOOST_AUTO_TEST_CASE(BadFormat) {
	std::vector<std::string> strings = {
		"--1",
		"+1",
		"1-2",
		"za",
		"123a123",
		"01",
		"-0",
		"-12a6",
		"-a1",
		"-9a9",
		"-01",
		"00",
		"0.0",
		"30.",
		"-.0",
	};
	
	for(const auto& s: strings){
		setStr(s);
		BOOST_CHECK_THROW(stream.read<int>(), ReadingException);
	}
	
}

BOOST_AUTO_TEST_CASE(CheckInRange) {
	setStr("1 -2 3");
	BOOST_CHECK_EQUAL(stream.read<int>(-5, 1), 1);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<int>(-100, 100), -2);
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<int>(5, 7), ReadingException);
}

BOOST_AUTO_TEST_CASE(Hex){
	setStr("ff");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), 255);
	
	setStr("g");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
	
	setStr("-a");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), -10);
}

BOOST_AUTO_TEST_CASE(HexCase){
	typedef HexReader<int>::Case Case;
	setStr("FF");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
	
	setStr("fF");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
	
	setStr("FF");
	BOOST_CHECK_NO_THROW(HexReader<int>(Case::UPPER).read(stream));
	
	setStr("ff");
	BOOST_CHECK_THROW(HexReader<int>(Case::UPPER).read(stream), ReadingException);
}

BOOST_AUTO_TEST_SUITE_END()

		
BOOST_FIXTURE_TEST_SUITE(NoStrictIntegers, NonStrictRead)


BOOST_AUTO_TEST_CASE(HexBoth){
	typedef HexReader<int>::Case Case;
	setStr("Ff");
	BOOST_CHECK_NO_THROW(HexReader<int>().read(stream));
	
	setStr("ff");
	BOOST_CHECK_THROW(HexReader<int>(Case::UPPER).read(stream), ReadingException);
}


BOOST_AUTO_TEST_SUITE_END()		