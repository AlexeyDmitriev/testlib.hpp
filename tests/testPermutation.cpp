#include <boost/test/unit_test.hpp>

#include "testlib/generators/int.hpp"

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
}

BOOST_AUTO_TEST_SUITE_END()


