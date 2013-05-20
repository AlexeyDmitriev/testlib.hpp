#include "testRandomTools.hpp"
#include <boost/test/unit_test.hpp>
#include <vector>
#include <set>
#include <string>
#include <list>
#include <deque>
#include <map>
#include "testlib/verdictFunctions.hpp"
#include "testlib/random.hpp"
#include "testlib/alias.hpp"
#include "testlib/generators/int.hpp"
#include "testlib/generators/float.hpp"
#include "testlib/generators/container.hpp"
#include "testlib/generators/unique.hpp"
#include "testlib/generators/pair.hpp"
#include "testlib/generatorWrapper.hpp"

BOOST_FIXTURE_TEST_SUITE(randomTest, RandomTest)

BOOST_AUTO_TEST_CASE(alias) {
	typedef Alias<int, OnesGenerator> One;
	for(int i = 0; i < 5; ++i) {
		BOOST_CHECK_EQUAL(rnd.next<One>(), 1);
	}
}

BOOST_AUTO_TEST_CASE(genWrapper) {
	auto generator = make_default_generator<int>(1, 5);
	int value = rnd.next<int>(generator);
	BOOST_CHECK(1 <= value && value <= 5);
}

BOOST_AUTO_TEST_CASE(basicRandom){
	int value = rnd.next<int>(5, 5);
	BOOST_CHECK_EQUAL(5, value);

	value = rnd.next<int>(5, 10);
	BOOST_CHECK(value >= 5 && value <= 10);

	rnd.fill(value, 42, 42);
	BOOST_CHECK_EQUAL(value, 42);
}

BOOST_AUTO_TEST_CASE(customGenerator) {

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

BOOST_AUTO_TEST_CASE(vectorTest){
	auto v = rnd.next<std::vector<int>>(5, OnesGenerator());
	std::vector<int> correct(5, 1);
	BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), correct.begin(), correct.end());
	
	v = rnd.next<std::vector<int>>(7, -100, 100);
	BOOST_CHECK_EQUAL(v.size(), 7);
	for(int x: v){
		BOOST_CHECK(x >= -100 && x <= 100);
	}

	auto copyRnd = rnd;

	std::vector<int> backInserter;
	std::vector<int> beginEnd(5);

	rnd.fillN<int>(5, back_inserter(backInserter));
	copyRnd.fillRange(beginEnd.begin(), beginEnd.end());
	BOOST_CHECK_EQUAL_COLLECTIONS(backInserter.begin(), backInserter.end(), beginEnd.begin(), beginEnd.end());

}

BOOST_AUTO_TEST_CASE(stringGen){
	auto s = rnd.next<std::string>(10, 'a', 'z');
	BOOST_CHECK_EQUAL(s.size(), 10);
	for(char c: s)
		BOOST_CHECK_MESSAGE(islower(c), c << " isn't lowercase letter");
}

BOOST_AUTO_TEST_CASE(genCollection) {
	//check only compilation
	auto d = rnd.next<std::deque<int>>(1);
	auto l = rnd.next<std::list<int>>(1);
	typedef std::pair<const int, char> pair;
	struct PairGenerator : public Generator<pair>{
		pair generate(Random& rnd) {
			return pair(0, 'a');
		}
	};
	auto m = rnd.next<std::map<int, char>>(1, PairGenerator());
	m = rnd.next<std::map<int, char>>(1);

	auto ms = rnd.next<std::multiset<std::string>>(2, 3, 'a', 'a');
	BOOST_CHECK_EQUAL(ms.size(), 2);
	BOOST_CHECK_EQUAL(*ms.begin(), "aaa");
}

BOOST_AUTO_TEST_CASE(checkStability){
	std::set<std::vector<int>> vectors;
	for(int i = 0; i < 10; ++i){
		auto copy = rnd;
		vectors.insert(copy.next<std::vector<int>>(10));
	}
	BOOST_CHECK_EQUAL(vectors.size(), 1);
}

BOOST_AUTO_TEST_CASE(testFloats) {
	for(int i = 0; i < 100; ++i){
		BOOST_CHECK(abs(rnd.next<double>(-1, 1)) <= 1.0);
	}
}

BOOST_AUTO_TEST_CASE(testAny) {
	std::set<int> s;
	for(int i = 0; i < 10; ++i){
		s.insert(rnd.next<int>());
	}
	BOOST_CHECK(s.find(rnd.any(s)) != s.end());
}

BOOST_AUTO_TEST_CASE(testUnique) {
	for(int i = 0; i < 5; ++i){
		std::vector<int> unique = rnd.next<std::vector<int>>(UniqueGenerator<std::vector<int>>(), 3, 1, 3);
		std::sort(unique.begin(), unique.end());
		int numberOfUnique = std::unique(unique.begin(), unique.end()) - unique.begin();
		BOOST_CHECK_EQUAL(numberOfUnique, 3);
	}


	for(int i = 0; i < 5; ++i) {
		std::set<int> unique = rnd.next<std::set<int>>(3, 1, 3);
		BOOST_CHECK_EQUAL(unique.size(), 3);
	}
}

BOOST_AUTO_TEST_SUITE_END()
