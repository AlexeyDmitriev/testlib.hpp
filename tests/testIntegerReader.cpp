#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "tests/fixture.hpp"
#include "testlib/testlib.hpp"


BOOST_FIXTURE_TEST_SUITE(Integers, SimpleRead)

BOOST_AUTO_TEST_CASE(RandomInts) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), 42);
	BOOST_CHECK_THROW(IntegerReader<int>().read(stream), ReadingException);

	setStr("-123 999");
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), -123);
	stream.readSpace();
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), 999);
}


BOOST_AUTO_TEST_CASE(Negative) {
	setStr("-517");
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), -517);
	
	setStr("-1");
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), -1);
	
	setStr("-1");
	BOOST_CHECK_THROW(IntegerReader<unsigned>().read(stream), ReadingException);
}


BOOST_AUTO_TEST_CASE(Overflow){
	setStr("65535 65535");
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), 65535);
	stream.readSpace();
	BOOST_CHECK_THROW(IntegerReader<short>().read(stream), ReadingException);
	
	setStr("9999999999999999999999999999999999999");
	BOOST_CHECK_THROW(IntegerReader<int>().read(stream), ReadingException);
	
	setStr("2000000000");
	BOOST_CHECK_NO_THROW(IntegerReader<int>().read(stream));
}

BOOST_AUTO_TEST_CASE(Corners){
	setStr("65535");
	BOOST_CHECK_NO_THROW(IntegerReader<unsigned short>().read(stream));
	
	setStr("65536");
	BOOST_CHECK_THROW(IntegerReader<unsigned short>().read(stream), ReadingException);
	
	setStr("-1");
	BOOST_CHECK_THROW(IntegerReader<unsigned short>().read(stream), ReadingException);
	
	
	setStr("32768");
	BOOST_CHECK_THROW(IntegerReader<short>().read(stream), ReadingException);
	
	setStr("-32768");
	BOOST_CHECK_NO_THROW(IntegerReader<short>().read(stream));
	
	setStr("-32769");
	BOOST_CHECK_THROW(IntegerReader<short>().read(stream), ReadingException);
	
	
	setStr("18446744073709551616");
	BOOST_CHECK_THROW(IntegerReader<unsigned long long>().read(stream), ReadingException);
	
	setStr("18446744073709551615");
	BOOST_CHECK_NO_THROW(IntegerReader<unsigned long long>().read(stream));
	
	
	setStr("9223372036854775808");
	BOOST_CHECK_THROW(IntegerReader<long long>().read(stream), ReadingException);
	
	setStr("9223372036854775807");
	BOOST_CHECK_NO_THROW(IntegerReader<long long>().read(stream));
	
	setStr("-9223372036854775809");
	BOOST_CHECK_THROW(IntegerReader<long long>().read(stream), ReadingException);
	
	setStr("-9223372036854775808");
	BOOST_CHECK_NO_THROW(IntegerReader<long long>().read(stream));
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
		"00"
	};
	
	for(const auto& s: strings){
		setStr(s);
		BOOST_CHECK_THROW(IntegerReader<int>().read(stream), ReadingException);
	}
	
}

BOOST_AUTO_TEST_CASE(CheckInRange) {
	setStr("1 -2 3");
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream, -5, 1), 1);
	stream.readSpace();
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream, -100, 100), -2);
	stream.readSpace();
	BOOST_CHECK_THROW(IntegerReader<int>().read(stream, 5, 7), ReadingException);
}

BOOST_AUTO_TEST_CASE(Hex){
	setStr("ff");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), 255);
	
	setStr("g");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
	
	setStr("-a");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), -10);
}


BOOST_AUTO_TEST_SUITE_END()
