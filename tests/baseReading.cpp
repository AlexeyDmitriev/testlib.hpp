#include <boost/test/unit_test.hpp>
#include "testlib/testlib.hpp"
#include "testlib/istream.hpp"
#include "tests/testTools.hpp"
#include "testlib/pair.hpp"

BOOST_FIXTURE_TEST_SUITE(baseStrict, StrictRead)

BOOST_AUTO_TEST_CASE( eof ) {
	setStr("");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr("");
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
	
	setStr(" ");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" ");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);

	setStr("\t");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);

	setStr("\t");
	BOOST_CHECK_EQUAL(stream.seekEof(), false);
}

BOOST_AUTO_TEST_CASE( chars ) {
	setStr("a bq");
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), ReadingException);
	
	setStr(" a bq");
	BOOST_CHECK_THROW(stream.readChar('a'), ReadingException);

	setStr("\ta ");
	BOOST_CHECK_NO_THROW(stream.readChar('\t'));
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readChar(' '));
	BOOST_CHECK_THROW(stream.readChar('\n'), ReadingException);
	
	setStr("\na ");
	BOOST_CHECK_NO_THROW(stream.readChar('\n'));
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readChar(' '));
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr("\t");
	BOOST_CHECK_EQUAL(stream.seekEoln(), false);
	setStr("\n");
	BOOST_CHECK_EQUAL(stream.seekEoln(), true);
}

BOOST_AUTO_TEST_CASE( tokens ){
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	setStr("token list");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.readToken(), "list");
	
	setStr("\ntoken");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	setStr("\t");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
}

BOOST_AUTO_TEST_CASE(spaces){
	setStr("  \t\n");
	BOOST_CHECK_EQUAL(stream.readChar(), ' ');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
	
	setStr("\n0+0=1");
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
	
	setStr("\n0+ 0= 1 ");
	BOOST_CHECK_EQUAL(stream.readChar(), '\n');
	BOOST_CHECK_EQUAL(stream.readToken(), "0+");
	BOOST_CHECK_EQUAL(stream.readChar(), ' ');
	BOOST_CHECK_EQUAL(stream.readToken(), "0=");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(baseNonStrict, NonStrictRead)

BOOST_AUTO_TEST_CASE( eof ) {
	
	
	setStr("");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" \n");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" lekha\n");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);
	
	setStr(" \npetr_is_cool_programmer");
	BOOST_CHECK_EQUAL(stream.seekEof(), false);
	
	setStr(" \n\t\n");
	BOOST_CHECK_EQUAL(stream.seekEof(), true);
}

BOOST_AUTO_TEST_CASE( eoln ) {
	
	
	setStr("");
	BOOST_CHECK_THROW(stream.readEoln(), ReadingException);
	
	setStr(" \n");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEoln());
	
	setStr(" \t \npetr_is_cool_programmer");
	BOOST_CHECK_EQUAL(stream.seekEoln(), true);
	
	setStr(" p\n    ");
	BOOST_CHECK_EQUAL(stream.seekEoln(), false);
	setStr(" \t\n p  ");
	BOOST_CHECK_EQUAL(stream.seekEoln(), true);
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
	BOOST_CHECK_EQUAL(stream.readToken(), "list");
	
	setStr("\ntoken");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	
	setStr(" lekha\n");
	BOOST_CHECK_EQUAL(stream.readToken(), "lekha");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
}

BOOST_AUTO_TEST_CASE(spaces){
	setStr("  p\t\nvictor");
	BOOST_CHECK_EQUAL(stream.readChar(), 'p');
	BOOST_CHECK_EQUAL(stream.readToken(), "victor");
	BOOST_CHECK_NO_THROW(stream.readEof())
}



BOOST_AUTO_TEST_CASE(super_test){
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
	BOOST_CHECK_NO_THROW(stream.readEof());
	
}

BOOST_AUTO_TEST_SUITE_END()
