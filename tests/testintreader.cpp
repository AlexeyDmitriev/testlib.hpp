/*
 * File:   testintreader.cpp
 * Author: riad
 *
 * Created on Sep 18, 2012, 10:09:32 PM
 */

#include "testintreader.hpp"

#include "testlib/testlib.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(testintreader);

testintreader::testintreader() {
}

testintreader::~testintreader() {
}

void testintreader::setUp() {
}

void testintreader::tearDown() {
}

void testintreader::testRandom() {
	std::stringstream ss;
	ss << "123";
	IStream stream(ss);
	CPPUNIT_ASSERT_EQUAL(123, stream.read<int>());
	ss.clear();
	ss << "-42 ";
	CPPUNIT_ASSERT_EQUAL(-42, stream.read<int>());
}

void testintreader::testCorner() {
	std::stringstream ss;
	ss << "0";
	IStream stream(ss);
	
	CPPUNIT_ASSERT_EQUAL(0, stream.read<int>());
	ss.clear();
	ss << (1LL<<31) - 1;
	CPPUNIT_ASSERT_EQUAL(int((1LL<<31) - 1), stream.read<int>());
}

void testintreader::testSigned(){
	std::stringstream ss;
	IStream stream(ss);
	ss << "65535";
	typedef unsigned short ushort;
	CPPUNIT_ASSERT_EQUAL(ushort(65535), stream.read<ushort>());
}

