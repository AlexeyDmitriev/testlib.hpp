#include "testTools.hpp"
#include <boost/test/unit_test.hpp>
#include <vector>
#include <set>
#include "testlib/verdictFunctions.hpp"
#include "testlib/random.hpp"
#include "testlib/generators/int.hpp"
BOOST_FIXTURE_TEST_SUITE(randomTest, RandomTest) 

BOOST_AUTO_TEST_CASE(basicRandom){
	int value = rnd.next<int>(5, 5);
	BOOST_CHECK_EQUAL(5, value);

	value = rnd.next<int>(5, 10);
	BOOST_CHECK(value >= 5 && value <= 10);
}

BOOST_AUTO_TEST_CASE(customGenerator) {
	struct OnesGenerator: public Generator<int>{
		int generate(Random&){
			return 1;
		}
	};

	OnesGenerator ones;

	for(int i = 0; i < 10; ++i){
		BOOST_CHECK_EQUAL(rnd.next<int>(ones), 1);
	}
}

BOOST_AUTO_TEST_CASE(shuffleTest) {
	std::vector<int> v;
	std::multiset<int> valuesBefore, valuesAfter;
	const int N = 100;
	for(int i = 0; i < N; ++i){
		int value = rnd.next<int>();
		v.push_back(value);
		valuesBefore.insert(value);
	}

	rnd.shuffle(v.begin(), v.end());

	for(int value: v){
		valuesAfter.insert(value);
	}

	BOOST_CHECK_EQUAL_COLLECTIONS(valuesBefore.begin(), valuesBefore.end(), valuesAfter.begin(), valuesAfter.end());
}

BOOST_AUTO_TEST_SUITE_END()
