#include <boost/test/unit_test.hpp>
#include "tests/testTools.hpp"
#include "testlib/alias.hpp"
#include "testlib/readers/int.hpp"
typedef Alias<int, HexReader<int>> Hex;
BOOST_FIXTURE_TEST_SUITE(aliasTest, StrictRead)

BOOST_AUTO_TEST_CASE(defaultRead){
	setStr("5");
	int x = stream.read<Hex>();
	BOOST_CHECK_EQUAL(x, 5);
	
	setStr("23");
	BOOST_CHECK_EQUAL(stream.read<Hex>(), 0x23);
}

BOOST_AUTO_TEST_CASE(argRead){
	setStr("7");
	BOOST_CHECK_EQUAL(stream.read<Hex>(1, 20), 7);
	
	setStr("7");
	BOOST_CHECK_THROW(stream.read<Hex>(10, 20), VerdictException);
}
		
BOOST_AUTO_TEST_SUITE_END()
