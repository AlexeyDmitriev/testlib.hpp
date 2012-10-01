#include <sstream>
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "testlib/testlib.hpp"


BOOST_AUTO_TEST_CASE(RandomDouble) {
	std::stringstream ss("42 17");
	IStream stream(ss);
	BOOST_CHECK_EQUAL(FloatReader<double>().read(stream), 42);
	BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);

        ss.str("-123.11 999.222 0.2");
	ss.clear();
	
	BOOST_CHECK_EQUAL(FloatReader<double>().read(stream), -123.11);
	stream.readSpace();
	BOOST_CHECK_EQUAL(FloatReader<double>().read(stream), 999.222);
        stream.readSpace();
	BOOST_CHECK_EQUAL(FloatReader<double>().read(stream), 0.2);
}


BOOST_AUTO_TEST_CASE(NegativeDouble) {
	std::stringstream ss("-517.512521");
	IStream stream(ss);
	
	BOOST_CHECK_EQUAL(FloatReader<double>().read(stream), -517.512521);
	
	ss.str("-1");
	ss.clear();
	BOOST_CHECK_EQUAL(FloatReader<double>().read(stream), -1);
	
	ss.str("-0.0");
	ss.clear();
	BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);
        
        ss.str("-0");
	ss.clear();
	BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);
        
        ss.str("-0.21");
	ss.clear();
	BOOST_CHECK_CLOSE(FloatReader<double>().read(stream), -0.21, 0.000001);
       
}

BOOST_AUTO_TEST_CASE(IncorrectSymbols) {
	std::stringstream ss;
	IStream stream(ss);
	std::vector<std::string> strings = {
		"za",
		"-12a6.0",
		"-a.1",
		"-9a.9",
	};
	
	for(const auto& s: strings){
		ss.str(s);
		ss.clear();
		BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);
	}
	
}

BOOST_AUTO_TEST_CASE(BadFormatMinuses) {
	std::stringstream ss;
	IStream stream(ss);
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
	
	for(const auto& s: strings){
		ss.str(s);
		ss.clear();
		BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);
	}
	
}

BOOST_AUTO_TEST_CASE(BadFormatTooManyPoints) {
	std::stringstream ss;
	IStream stream(ss);
	std::vector<std::string> strings = {
		"-1.0000.",
		"+0..000",
		".2",
		"123.12.3",
		".1",
		"-.0"
	};
	
	for(const auto& s: strings){
		ss.str(s);
		ss.clear();
		BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);
	}
	
}

BOOST_AUTO_TEST_CASE(WrongNumbersSize) {
	std::stringstream ss;
	IStream stream(ss);
	std::vector<std::string> strings;
        std::string curString;
        for (int i = 0; i < 1000; ++i){
            curString.resize(curString.size() + 1);
            curString.back() = '1';
	}
        
        strings.push_back(curString);
        
	for(const auto& s: strings){
		ss.str(s);
		ss.clear();
		BOOST_CHECK_THROW(FloatReader<double>().read(stream), ReadingException);
	}
}