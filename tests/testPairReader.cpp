#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/testlib.hpp"
#include "testlib/pair.hpp"
#include "testTools.hpp"
#include "testlib/readerWrapper.hpp"

using std::pair;

typedef pair<int, long long> pil;
typedef pair<int, unsigned> piu;
typedef pair<int, int> pi;

BOOST_FIXTURE_TEST_SUITE(Pairs, NonStrictRead)

BOOST_AUTO_TEST_CASE(testRandom){
	setStr("12 -1");
	BOOST_CHECK_EQUAL(stream.read<pil>(), std::make_pair(12, -1LL));
	
	setStr("12 -1");
	BOOST_CHECK_THROW(stream.read<piu>(), ReadingException);
}

BOOST_AUTO_TEST_CASE(customReaders){
	
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
	
	setStr("42 17");
	BOOST_CHECK_THROW(stream.read<pi>(upTo20, any), ReadingException);
	
	setStr("42 17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(any, upTo20));
	
	setStr("123 456");
	BOOST_CHECK_NO_THROW(stream.read<pi>(make_default_reader<int>(100, 1000)));
	
	setStr("123 456");
	BOOST_CHECK_THROW(stream.read<pi>(make_default_reader<int>(100, 200)), ReadingException);
}

BOOST_AUTO_TEST_CASE(Separators){
	setStr("123\n345");
	BOOST_CHECK_NO_THROW(stream.read<pi>());
	
	setStr("123vs345");
	BOOST_CHECK_THROW(stream.read<pi>("vs"), ReadingException);
	
	setStr("123 vs345");
	BOOST_CHECK_NO_THROW(stream.read<pi>("vs"));
	
	setStr("123 vs 345");
	auto upTo20 = make_default_reader<int>(0, 20);
	BOOST_CHECK_THROW(stream.read<pi>(upTo20, upTo20, "vs"), ReadingException);
}

BOOST_AUTO_TEST_CASE(DifferentTypes){

	typedef pair<unsigned int, int> p_UI_I;
	setStr("-123\n345");
	BOOST_CHECK_THROW(stream.read<p_UI_I>(), ReadingException);

	setStr("-123\n345");
	BOOST_CHECK_THROW(stream.read<p_UI_I>(), ReadingException);

	typedef pair<int, double> p_I_D;
	setStr("-123.0\n345");
	BOOST_CHECK_THROW(stream.read<p_I_D>(), ReadingException);

	typedef pair<int, double> p_S_D;
	setStr("-123 -345.0");
	BOOST_CHECK_EQUAL(stream.read<p_S_D>("-"), std::make_pair(-123, 345.0));
	
	typedef pair<int, double> p_S_D;
	setStr("-123 --345.0");
	BOOST_CHECK_EQUAL(stream.read<p_S_D>("-"), std::make_pair(-123, -345.0));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(StrictPairs, StrictRead)
BOOST_AUTO_TEST_CASE(StrictSeparators){
	setStr("123\n345");
	BOOST_CHECK_THROW(stream.read<pi>(), ReadingException);
	
	setStr("123\n345");
	BOOST_CHECK_NO_THROW(stream.read<pi>('\n'));
	
	setStr("123 vs345");
	BOOST_CHECK_THROW(stream.read<pi>("vs"), ReadingException);
	
	setStr("123 vs345");
	BOOST_CHECK_NO_THROW(stream.read<pi>(" vs"));
}

BOOST_AUTO_TEST_SUITE_END()
