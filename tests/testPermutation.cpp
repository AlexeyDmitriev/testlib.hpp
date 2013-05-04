#include <boost/test/unit_test.hpp>

#include <set>
#include <vector>

#include "testlib/generators/int.hpp"
#include "testlib/generators/float.hpp"

#include "libs/permutation/permutation.hpp"

#include "testReadTools.hpp"
#include "testRandomTools.hpp"
using std::vector;
BOOST_FIXTURE_TEST_SUITE(PermutationRandom, RandomTest)

BOOST_AUTO_TEST_CASE(inverse) {
	for(int i = 0; i < 10; ++i) {
		int n = rnd.next<int>(5, 10);
		Permutation p = rnd.next<Permutation>(n);
		BOOST_CHECK_EQUAL(p * p.inverse(), Permutation::identity(n));
	}
}

BOOST_AUTO_TEST_CASE(construction) {
	BOOST_CHECK_NO_THROW(Permutation(std::vector<size_t>()));
	BOOST_CHECK_NO_THROW(Permutation(std::vector<size_t>{1, 2, 0}));

	BOOST_CHECK_THROW(Permutation(std::vector<size_t>{1, 2, 3}), VerdictException);
	BOOST_CHECK_THROW(Permutation(std::vector<size_t>{1, 2, 1}), VerdictException);
}

BOOST_AUTO_TEST_CASE(multiplying) {

	for(int i = 0; i < 5; ++i) {
		Permutation a = Permutation::identity(3);
		Permutation b = rnd.next<Permutation>(3);

		BOOST_CHECK_EQUAL(a * b, b);
		BOOST_CHECK_EQUAL(b * a, b);
	}

	Permutation x = Permutation(std::vector<size_t>{1, 2, 0});
	Permutation y = Permutation(std::vector<size_t>{0, 2, 1});

	Permutation xy = Permutation(std::vector<size_t>{1, 0, 2});
	Permutation yx = Permutation(std::vector<size_t>{2, 1, 0});

	BOOST_CHECK_EQUAL(x * y, xy);
	BOOST_CHECK_EQUAL(y * x, yx);
}

BOOST_AUTO_TEST_CASE(applying) {
	std::vector<double> doubles;
	for(int i = 0; i < 10; ++i) {
		doubles.push_back(rnd.next<double>(-1.0, 1.0));
	}
	std::multiset<double> set(doubles.begin(), doubles.end());


	for(int i = 0; i < 5; ++i) {
		Permutation p = rnd.next<Permutation>(10);
		p.applyTo(doubles);

		std::multiset<double> newSet(doubles.begin(), doubles.end());

		BOOST_CHECK_EQUAL_COLLECTIONS(set.begin(), set.end(), newSet.begin(), newSet.end());
	}
}

BOOST_AUTO_TEST_CASE(sizes) {
	Permutation a = Permutation::identity(3);
	Permutation b = Permutation::identity(2);
	BOOST_CHECK_THROW(a * b, VerdictException);
	BOOST_CHECK_THROW(a < b, VerdictException);
	BOOST_CHECK_THROW(b == a, VerdictException);

	BOOST_CHECK_NO_THROW(a * a);
}

BOOST_AUTO_TEST_SUITE_END()


