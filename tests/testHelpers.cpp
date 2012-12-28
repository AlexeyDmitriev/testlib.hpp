#include "testTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testlib/float.hpp"
#include "testlib/verdictFunctions.hpp"
#include <algorithm>
#include <vector>
BOOST_AUTO_TEST_CASE(doubleEqual){
	BOOST_CHECK(areClose(1.0, 1.0, 1e-8));
	
	BOOST_CHECK(areClose(1.0, 1.0 + 1e-15, 1e-8));
	
	BOOST_CHECK(!areClose(1.0, 1 + 1e-7, 1e-8));
	
	BOOST_CHECK(areClose(100.0, 100 + 1e-7, 1e-8));
	
	BOOST_CHECK(areClose(0.01, 0.01 + 1e-9, 1e-8));
	
	BOOST_CHECK(!areClose(1.0,100.0, 1e-8));
	
	BOOST_CHECK(!areClose(100.0, 1.0, 1e-8));
}

BOOST_AUTO_TEST_CASE(equalRanges){
	using std::vector;
	vector<int> a = {2, 1, 3};
	vector<int> b = {1, 2, 3};
	BOOST_CHECK_THROW(verifyEqualRanges(a.begin(), a.end(), b.begin(), b.end()), VerdictException);
	
	std::sort(a.begin(), a.end());
	BOOST_CHECK_NO_THROW(verifyEqualRanges(a.begin(), a.end(), b.begin(), b.end()));
	
	BOOST_CHECK_THROW(verifyEqualRanges(a.begin(), a.begin() + 2, b.begin(), b.end()), VerdictException);
	
	
	vector<int> c = {1, 3, 5};
	BOOST_CHECK_THROW(verifyEqualRanges(a.begin(), a.end(), c.begin(), c.end()), VerdictException);
}