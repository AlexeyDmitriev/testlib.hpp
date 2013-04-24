#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/readers/pair.hpp"
#include "testlib/readers/int.hpp"
#include "testlib/readers/float.hpp"
#include "testlib/readerWrapper.hpp"
#include "testReadTools.hpp"
#include "libs/unorderedPair.hpp"

typedef UnorderedPair<int> pi;

template<typename T>
std::ostream& operator << (std::ostream& stream, UnorderedPair<T> const & p){
	return stream << '{' << p.first << ',' << p.second << '}' << std::endl;
}

BOOST_FIXTURE_TEST_SUITE(UnorderedPairs, StrictRead)

#include "testUnorderedPair/allOk.hpp"
#include "testUnorderedPair/allFail.hpp"
#include "testUnorderedPair/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()
