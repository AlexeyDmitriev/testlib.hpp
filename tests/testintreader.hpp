/*
 * File:   testintreader.hpp
 * Author: riad
 *
 * Created on Sep 18, 2012, 10:09:32 PM
 */

#ifndef TESTINTREADER_HPP
#define	TESTINTREADER_HPP

#include <cppunit/extensions/HelperMacros.h>

class testintreader : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(testintreader);

	CPPUNIT_TEST(testRandom);
	CPPUNIT_TEST(testCorner);
	CPPUNIT_TEST(testSigned);

	CPPUNIT_TEST_SUITE_END();

public:
	testintreader();
	virtual ~testintreader();
	void setUp();
	void tearDown();

private:
	void testRandom();
	void testSigned();
	void testCorner();
};

#endif	/* TESTINTREADER_HPP */

