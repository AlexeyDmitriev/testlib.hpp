#include <boost/test/unit_test.hpp>
#include "testlib/testlib.hpp"
#include "testlib/istream.hpp"
#include "tests/testTools.hpp"
#include "testlib/pair.hpp"
#include "testBaseReading/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(baseStrict, StrictRead)

#include "testBaseReading/allOk.hpp"
#include "testBaseReading/allFail.hpp"
#include "testBaseReading/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(baseNonStrict, NonStrictRead)

#include "testBaseReading/allOk.hpp"
#include "testBaseReading/allFail.hpp"
#include "testBaseReading/strictFail.hpp"

BOOST_AUTO_TEST_CASE(eofStrict) {	
//	setStr(" \n");
//	BOOST_CHECK_NO_THROW(stream.readEof());
		
	setStr(" \n\t\n");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEof(), true);
	
	setStr("\n");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEof(), true);
	
	setStr("4\n");
	BOOST_CHECK_EQUAL(stream.read<int>(), 4);
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEof(), true);
}

BOOST_AUTO_TEST_CASE(eolnStrict) {
	setStr(" \t \npetr_is_cool_programmer");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEoln(), true);
	
	setStr(" \t\n p  ");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEoln(), true);
}

BOOST_AUTO_TEST_CASE(superTestNonStrict){
	setStr("3 3\naba p -3 1 \np anya 1.0 1\nanya   \t aba -0.0 -21\n    \n");
	BOOST_CHECK_EQUAL(stream.read<short>(), 3);
	BOOST_CHECK_EQUAL(stream.read<int>(), 3);
	BOOST_CHECK_EQUAL(stream.readToken(), "aba");
	BOOST_CHECK_EQUAL(stream.readChar(), 'p');
	BOOST_CHECK_EQUAL(stream.read<double>(), -3);
	BOOST_CHECK_EQUAL(stream.read<int>(), 1);
	BOOST_CHECK_EQUAL(stream.readToken(), "p");
	BOOST_CHECK_EQUAL(stream.readToken(), "anya");
	BOOST_CHECK_EQUAL(stream.read<double>(), 1);
	BOOST_CHECK_EQUAL(stream.read<unsigned short>(), 1);
	
	BOOST_CHECK_EQUAL(stream.readToken(), "anya");
	BOOST_CHECK_EQUAL(stream.readToken(), "aba");	
	
	typedef std::pair<double, int> T;
	std::pair<double, int> p(0, -21);
	BOOST_CHECK_EQUAL(stream.read<T>(), p);
}

BOOST_AUTO_TEST_CASE(spaces){
	setStr("  p\t\nvictor");
	BOOST_CHECK_EQUAL(stream.readChar(), 'p');
	BOOST_CHECK_EQUAL(stream.readToken(), "victor");
	BOOST_CHECK_NO_THROW(stream.readEof())
}

BOOST_AUTO_TEST_SUITE_END()
