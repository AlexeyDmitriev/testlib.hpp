
#include "testlib/istream.hpp"

#include <boost/test/unit_test.hpp>

#include "testlib/testlib.hpp"
#include <sstream>

using std::stringstream;

BOOST_AUTO_TEST_CASE( eof ) {
	stringstream ss;
	IStream stream(ss);
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	ss.clear();
	ss.str(" ");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	ss.clear();
	ss.str(" ");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);
}

BOOST_AUTO_TEST_CASE( chars ) {
	stringstream ss("a bq");
	IStream stream(ss);
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), ReadingException);
}

BOOST_AUTO_TEST_CASE( tokens ){
	stringstream ss;
	
	IStream stream(ss);
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	
	ss.clear();
	ss.str("token list");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	ss.clear();
	ss.str("\ntoken");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
}

BOOST_AUTO_TEST_CASE(spaces){
	stringstream ss("  \t\n");
	IStream stream(ss);
	
	BOOST_CHECK_EQUAL(stream.readChar(), ' ');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
}
