#include <vector>
#include <boost/test/unit_test.hpp>
#include "tests/testTools.hpp"
#include "testlib/core.hpp"
#include "testlib/readers/vector.hpp"
#include "testlib/verdictFunctions.hpp"

using std::vector;
BOOST_FIXTURE_TEST_SUITE(verdictTest, StrictRead)

BOOST_AUTO_TEST_CASE(verdictEqual){
	verifyEqual(51, 6, Verdict::WA, std::greater<int>());
	verifyEqual(51, 6, Verdict::PE, std::greater<int>());
	verifyEqual(51, 6, Verdict::PE, std::not_equal_to<int>());
	BOOST_CHECK_THROW(verifyEqual(51, 66, Verdict::PE, std::greater<int>()), VerdictException);
	verifyEqual(6, 6, Verdict::PE);
	BOOST_CHECK_THROW(verifyEqual(5, 6, Verdict::PE), VerdictException);
	verifyEqual(6, 6);
	BOOST_CHECK_THROW(verifyEqual(5, 6), VerdictException);
	
}

BOOST_AUTO_TEST_CASE(verdictSorted){
	vector<int> a(4);
	for (int i = 0; i < 4; ++i) 
		a[i] = i;
	verifySorted(a.begin(), a.end(), Verdict::WA, std::less<int>());
	BOOST_CHECK_THROW(verifySorted(a.begin(), a.end(), Verdict::WA, std::greater<int>()), VerdictException);
	verifySorted(a.begin(), a.end(), Verdict::WA);
	BOOST_CHECK_THROW(verifySorted(a.rbegin(), a.rend(), Verdict::FAIL), VerdictException);
	verifySorted(a.begin(), a.end());
	BOOST_CHECK_THROW(verifySorted(a.rbegin(), a.rend()), VerdictException);
}

BOOST_AUTO_TEST_SUITE_END()
