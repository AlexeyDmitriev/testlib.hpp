#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "tests/testTools.hpp"
#include "testlib/testlib.hpp"

std::string getNextString(std::string s)
{
	std::string res = s;
	if (res[0] == '-')
		res[res.size() - 1]--;
	else
		res[res.size() - 1]++;
	return res;
}

std::string getPrevString(std::string s)
{
	if (s == "0")
		return "-1";
	std::string res = s;
	if (s[0] == '-')
		res[res.size() - 1]++;
	else
		res[res.size() - 1]--;
	return res;
}

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


BOOST_AUTO_TEST_CASE(Overflow)
{
	setStr("65535 65535");
	BOOST_CHECK_EQUAL(stream.read<int>(), 65535);
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<short>(), ReadingException);

	setStr("2147483647 -9223372036854775810");
	BOOST_CHECK_NO_THROW(stream.read<int>());
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<long long>(), ReadingException);

	setStr("9999999999999999999999999999999999999");
	BOOST_CHECK_THROW(stream.read<int>(), ReadingException);

	setStr("2000000000");
	BOOST_CHECK_NO_THROW(stream.read<int>());
}

template <typename T>
void testCorners(StrictRead& in) {
	in.setStr(toString(std::numeric_limits<T>::min()));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
	in.setStr(toString(std::numeric_limits<T>::max()));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());

	in.setStr(getPrevString(toString(std::numeric_limits<T>::min())));
	BOOST_CHECK_THROW(in.stream.read<T>(), ReadingException);
	in.setStr(getNextString(toString(std::numeric_limits<T>::max())));
	BOOST_CHECK_THROW(in.stream.read<T>(), ReadingException);
	in.setStr(getPrevString(toString(std::numeric_limits<T>::max())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
	in.setStr(getNextString(toString(std::numeric_limits<T>::min())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
}

BOOST_AUTO_TEST_CASE(Corners)
{
	testCorners<int>(*this);
	testCorners<long long>(*this);
	testCorners<short>(*this);

	testCorners<unsigned int>(*this);
	testCorners<unsigned long long>(*this);
	testCorners<unsigned short>(*this);
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
		"-.2",
		"-2.0",
		".1",
		"2.2"
	};

	for(const auto& s: strings) {
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
	for(int i = 0; i < 1000; i++) {
		int m = 1;
		if (rnd() % 2 == 1)
			m = -1;
		m *= (rnd() % (i + 1));
		setStr(toString(m));
		BOOST_CHECK_EQUAL(stream.read<int>(-i, i), m);
	}
	for(int i = 0; i < 10000; i++) {
		int l = rnd();
		int r = l + rnd() + 1;
		int m = rnd();
		setStr(toString(m));
		if (l <= m && m <= r)
			BOOST_CHECK_EQUAL(stream.read<int>(l, r), m);
		else
			BOOST_CHECK_THROW(stream.read<int>(l, r), ReadingException);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(HexIntegers, StrictRead)

template <typename T>
std::string toHex(T val) {
	if (val == 0)
		return "0";
	std::string res;
	T c = val;
	if (c > 0) 
		c = -c;
	while (c) {
		if (abs(c % 16) >= 10)
			res += char('a' + abs(c % 16) - 10);
		else
			res += char('0' + abs(c % 16));
		c /= 16;
	}
	std::reverse(res.begin(), res.end());
	if (val < 0)
		res = "-" + res;
	return res;
}
 
BOOST_AUTO_TEST_CASE(HexSimple)
{ 
	setStr("ff");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), 255);
 
	setStr("fa");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), 250);
 
	for (int i = -10000; i <= 10000; i++){
		setStr(toHex(i));
		//std::cerr << toHex(i) << std::endl;
		BOOST_CHECK_EQUAL(HexReader<int>().read(stream), i);
		BOOST_CHECK_THROW(HexReader<int>().read(stream, i + 1, i + 2), ReadingException);
	}

	setStr("g");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
 
	setStr("-a");
	BOOST_CHECK_EQUAL(HexReader<int>().read(stream), -10);
}


BOOST_AUTO_TEST_CASE(HexBadFormat) {
	std::vector<std::string> strings = {
		"--1",
		"+1",
		"1-2",
		"za",
		"123a123",
		"01",
		"-0",
		"-12g6",
		"-a1F",
		"-9Aa9",
		"-01",
		"00",
		"0.0",
		"30.",
		"-.0",
		"-.2",
		"-2.0",
		".1",
		"2.2"
	};

	for(const auto& s: strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<int>(), ReadingException);
	}
	for (int i = -10; i < 100; i++) {
		std::string res;
		int c = abs(i);
		bool good = true;
		while (c) {
			if (c % 36 >= 10) {
				res += char('a' + c % 36 - 10);
				if (c % 36 >= 16)
					good = false;
			}
			else
				res += char('0' + c % 36);
			c /= 36;
		}	
		std::reverse(res.begin(), res.end());
		if (i < 0)
			res = "-" + res;
		if (i == 0)
			res = "0";
		setStr(res);
		if (good){
			BOOST_CHECK_NO_THROW(HexReader<int>().read(stream));
		}
		else{
			BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
		}
	}
}

template <typename T>
void testCorners(StrictRead& in) {	
	
	in.setStr(toHex(std::numeric_limits<T>::min()));
	BOOST_CHECK_NO_THROW(HexReader<T>().read(in.stream));
	in.setStr(toHex(std::numeric_limits<T>::max()));
	BOOST_CHECK_NO_THROW(in.stream.read<T>(HexReader<T>()));


	in.setStr(getPrevString(toString(std::numeric_limits<T>::min())));
	BOOST_CHECK_THROW(in.stream.read<T>(), ReadingException);
	in.setStr(getNextString(toString(std::numeric_limits<T>::max())));
	BOOST_CHECK_THROW(in.stream.read<T>(), ReadingException);
	in.setStr(getPrevString(toString(std::numeric_limits<T>::max())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
	in.setStr(getNextString(toString(std::numeric_limits<T>::min())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());

}


BOOST_AUTO_TEST_CASE(HexCorners)
{
	testCorners<int>(*this);
	testCorners<long long>(*this);
	testCorners<short>(*this);

	testCorners<unsigned int>(*this);
	testCorners<unsigned long long>(*this);
	testCorners<unsigned short>(*this);
}
 
BOOST_AUTO_TEST_CASE(HexCase)
{
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


BOOST_AUTO_TEST_CASE(HexBoth)
{
	typedef HexReader<int>::Case Case;
	setStr("Ff");
	BOOST_CHECK_NO_THROW(HexReader<int>().read(stream));
 
	setStr("ff");
	BOOST_CHECK_THROW(HexReader<int>(Case::UPPER).read(stream), ReadingException);
}
 
 
BOOST_AUTO_TEST_SUITE_END()
 