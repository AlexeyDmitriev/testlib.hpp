#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "testlib/testlib.hpp"
#include "tests/testTools.hpp"

double randomDouble(){
	return ((double)rnd() * rnd()) / (rnd() + 1);
}

BOOST_FIXTURE_TEST_SUITE(Doubles, StrictRead)

BOOST_AUTO_TEST_CASE(RandomDouble) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<double>(), 42);
	BOOST_CHECK_THROW(stream.read<double>(), ReadingException);

	setStr("-123.11 999.222 0.2");
	BOOST_CHECK_EQUAL(stream.read<double>(), -123.11);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<double>(), 999.222);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<double>(), 0.2);
}

BOOST_AUTO_TEST_CASE(NegativeDouble) {
	setStr("-517.512521");
	BOOST_CHECK_EQUAL(stream.read<double>(), -517.512521);

	setStr("-1");
	BOOST_CHECK_EQUAL(stream.read<double>(), -1);

	setStr("-0.0");
	BOOST_CHECK_EQUAL(stream.read<double>(), 0);
	
	setStr("-0");
	BOOST_CHECK_EQUAL(stream.read<double>(), 0);

	setStr("-0.21");
	BOOST_CHECK_EQUAL(stream.read<double>(), -0.21);
}

BOOST_AUTO_TEST_CASE(IncorrectSymbols) {
	std::vector<std::string> strings = {
		"za",
		"-12a6.0",
		"-a.1",
		"-9a.9",
	};

	for (const auto& s : strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<double>(), ReadingException);
	}

}

BOOST_AUTO_TEST_CASE(BadFormatMinuses) {
	std::vector<std::string> strings = {
		"--1",
		"+-1",
		"1-2",
		"za",
		"123+a123",
		"-+01",
		"-12a6",
		"-a.1",
		"-99.a",
		"-01",
		"0+0"
	};

	for (const auto& s : strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<double>(), ReadingException);
	}

}

BOOST_AUTO_TEST_CASE(BadFormatTooManyPoints) {
	std::vector<std::string> strings = {
		"-1.0000.",
		"+0..000",
		".2",
		"123.12.3",
		".1",
		"-.0",
		"-.17",
		"-1.",
	};

	for (const auto& s : strings) {
		setStr(s);\
		BOOST_CHECK_THROW(stream.read<double>(), ReadingException);
	}

}

BOOST_AUTO_TEST_CASE(WrongNumbersSize) {
	std::string curString(1000, '1');

	setStr(curString);
	BOOST_CHECK_THROW(stream.read<double>(), ReadingException);
}

BOOST_AUTO_TEST_CASE(NormalWorkingWithSpaces){
	setStr("-517.512521 2.4990");
	BOOST_CHECK_EQUAL(stream.read<double>(), -517.512521);
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.read<double>(), 2.4990);
	
	setStr("-517.\n");
	BOOST_CHECK_THROW(stream.read<double>(), ReadingException);
}

/*
BOOST_AUTO_TEST_CASE(DoubleCheckInRange) {
	for(int i = 0; i < 1; i++){
		double l = randomDouble();
		double r = l + randomDouble() + 0.1;
		double m = randomDouble();
		setStr(toString(m));
		std::cout << l << " " << m << " " << r << std::endl;
		if (l <= m && m <= r)
			BOOST_CHECK_EQUAL(stream.read<double>(l, r), m);
		else
			BOOST_CHECK_THROW(stream.read<double>(l, r), ReadingException);
	}
}*/
BOOST_AUTO_TEST_SUITE_END()
