#include <sstream>
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "testlib/testlib.hpp"


BOOST_AUTO_TEST_CASE(RandomInts) {
	std::stringstream ss("42 17");
	IStream stream(ss);
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), 42);
	BOOST_CHECK_THROW(IntegerReader<int>().read(stream), ReadingException);

	ss.str("-123 999");
	ss.clear();
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), -123);
	stream.readSpace();
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), 999);
}


BOOST_AUTO_TEST_CASE(Negative) {
	std::stringstream ss("-517");
	IStream stream(ss);
	
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), -517);
	
	ss.str("-1");
	ss.clear();
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), -1);
	
	ss.str("-1");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<unsigned>().read(stream), ReadingException);
	
}


BOOST_AUTO_TEST_CASE(Overflow){
	std::stringstream ss("65535 65535");
	IStream stream(ss);
	
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream), 65535);
	stream.readSpace();
	BOOST_CHECK_THROW(IntegerReader<short>().read(stream), ReadingException);
	
	ss.str("9999999999999999999999999999999999999");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<int>().read(stream), ReadingException);
	
	ss.str("2000000000");
	ss.clear();
	BOOST_CHECK_NO_THROW(IntegerReader<int>().read(stream));
}

BOOST_AUTO_TEST_CASE(Corners){
	std::stringstream ss("65535");
	IStream stream(ss);
	
	BOOST_CHECK_NO_THROW(IntegerReader<unsigned short>().read(stream));
	
	ss.str("65536");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<unsigned short>().read(stream), ReadingException);
	
	ss.str("-1");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<unsigned short>().read(stream), ReadingException);
	
	
	ss.str("32768");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<short>().read(stream), ReadingException);
	
	ss.str("-32768");
	ss.clear();
	BOOST_CHECK_NO_THROW(IntegerReader<short>().read(stream));
	
	ss.str("-32769");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<short>().read(stream), ReadingException);
	
	ss.str("18446744073709551616");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<unsigned long long>().read(stream), ReadingException);
	
	ss.str("18446744073709551615");
	ss.clear();
	BOOST_CHECK_NO_THROW(IntegerReader<unsigned long long>().read(stream));
	
	
	ss.str("9223372036854775808");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<long long>().read(stream), ReadingException);
	
	ss.str("9223372036854775807");
	ss.clear();
	BOOST_CHECK_NO_THROW(IntegerReader<long long>().read(stream));
	
	ss.str("-9223372036854775809");
	ss.clear();
	BOOST_CHECK_THROW(IntegerReader<long long>().read(stream), ReadingException);
	
	ss.str("-9223372036854775808");
	ss.clear();
	BOOST_CHECK_NO_THROW(IntegerReader<long long>().read(stream));
}

BOOST_AUTO_TEST_CASE(BadFormat) {
	std::stringstream ss;
	IStream stream(ss);
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
		ss.str(s);
		ss.clear();
		BOOST_CHECK_THROW(IntegerReader<int>().read(stream), ReadingException);
	}
	
}

BOOST_AUTO_TEST_CASE(CheckInRange) {
	std::stringstream ss("1 -2 3");
	IStream stream(ss);
	
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream, -5, 1), 1);
	stream.readSpace();
	BOOST_CHECK_EQUAL(IntegerReader<int>().read(stream, -100, 100), -2);
	stream.readSpace();
	BOOST_CHECK_THROW(IntegerReader<int>().read(stream, 5, 7), ReadingException);

}