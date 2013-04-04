#include <boost/test/unit_test.hpp>
#include "testlib/istream.hpp"
#include "testlib/readers/int.hpp"
#include "testlib/readers/float.hpp"
#include "tests/testTools.hpp"
#include "testlib/readers/pair.hpp"
#include "testBaseReading/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(baseStrict, StrictRead)

#include "testBaseReading/allOk.hpp"
#include "testBaseReading/allFail.hpp"
#include "testBaseReading/strictFail.hpp"

BOOST_AUTO_TEST_CASE(spacesExampleStrict){
	setStr("  \t\n");
	BOOST_CHECK_EQUAL(stream.readChar(), ' ');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_THROW(stream.readSpace(), VerdictException);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(baseNonStrict, NonStrictRead)

#include "testBaseReading/allOk.hpp"
#include "testBaseReading/allFail.hpp"
#include "testBaseReading/strictFail.hpp"

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

BOOST_AUTO_TEST_CASE(spacesNonStrictExample){
	setStr("  p\t\nvictor");
	BOOST_CHECK_EQUAL(stream.readChar(), 'p');
	BOOST_CHECK_EQUAL(stream.readToken(), "victor");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr("  \t\n");
	BOOST_CHECK_THROW(stream.readChar(), VerdictException);
}
BOOST_AUTO_TEST_SUITE_END()
