#include <boost/test/unit_test.hpp>
#include "testlib/testlib.hpp"
#include "testlib/istream.hpp"
#include "tests/fixture.hpp"

BOOST_FIXTURE_TEST_SUITE(base, SimpleRead)

BOOST_AUTO_TEST_CASE( eof ) {
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" ");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" ");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);
}

BOOST_AUTO_TEST_CASE( chars ) {
	setStr("a bq");
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), ReadingException);
}

BOOST_AUTO_TEST_CASE( tokens ){
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	setStr("token list");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	setStr("\ntoken");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
}

BOOST_AUTO_TEST_CASE(spaces){
	setStr("  \t\n");
	BOOST_CHECK_EQUAL(stream.readChar(), ' ');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
}


BOOST_AUTO_TEST_SUITE_END()
