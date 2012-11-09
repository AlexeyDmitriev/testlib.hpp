#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "testlib/testlib.hpp"
#include "tests/testTools.hpp"
#include <boost/test/unit_test.hpp>
#include "tests/testInteger/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(Integers, StrictRead)

#include "testInteger/allOk.hpp"
#include "testInteger/allFail.hpp"
#include "testInteger/StrictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

		
/*
template <typename T>
void testPairs(StrictRead& in, T l1, T r1, T l2, T r2) {	
	for (T i = l1; i <= r1; i++)
		for (T j = l2; j <= r2; j++)
		{
			in.setStr(toHex<T>(i) + " " + toHex<T>(j));
			BOOST_CHECK_EQUAL(in.stream.read<T>(HexReader<T>()), i);
			BOOST_CHECK_NO_THROW(in.stream.readSpace());
			BOOST_CHECK_EQUAL(in.stream.read<T>(HexReader<T>()), j);
		}
}

BOOST_AUTO_TEST_CASE(PairInts) {
	testPairs<int>(*this, -110, 50, -110, 50);
	testPairs<long long>(*this, -1e10, -1e10 + 100, -1e18 - 20, -1e18);
	testPairs<short>(*this, -110, 50, -110, 50);
	
				
	testPairs<unsigned int>(*this, 500, 550, 100000, 100050);
	testPairs<unsigned long long>(*this, 1e10, 1e10 + 100, 1e18 - 20, 1e18);
	testPairs<unsigned short>(*this, 110, 150, 110, 150);
}

// UNDER THAT MUST BE CONTINUE
BOOST_AUTO_TEST_CASE(HexCase)
{
	typedef HexReader<int>::Case Case;
	setStr("FF");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);

	setStr("fF");
	BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);

	setStr("FF");
	BOOST_CHECK_NO_THROW(HexReader<int>(Case::UPPER).read(stream));

	setStr("ff");
	BOOST_CHECK_THROW(HexReader<int>(Case::UPPER).read(stream), ReadingException);
}

BOOST_AUTO_TEST_SUITE_END()
*/

BOOST_FIXTURE_TEST_SUITE(NoStrictIntegers, NonStrictRead)

#include "testInteger/allOk.hpp"
#include "testInteger/allFail.hpp"


BOOST_AUTO_TEST_CASE(HexBoth){
	typedef HexReader<int>::Case Case;
	setStr("Ff");
	BOOST_CHECK_NO_THROW(HexReader<int>().read(stream));
 
	setStr("ff");
	BOOST_CHECK_THROW(HexReader<int>(Case::UPPER).read(stream), ReadingException);
}
 
 
BOOST_AUTO_TEST_SUITE_END()
 