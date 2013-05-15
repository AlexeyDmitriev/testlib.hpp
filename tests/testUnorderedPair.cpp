#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/readers/pair.hpp"
#include "testlib/readers/int.hpp"
#include "testlib/readers/float.hpp"
#include "testlib/readerWrapper.hpp"
#include "testReadTools.hpp"
#include "testRandomTools.hpp"
#include "libs/unorderedPair.hpp"
#include "testlib/generators/int.hpp"

typedef UnorderedPair<int> pi;
typedef UnorderedPair<std::string> ps;

BOOST_FIXTURE_TEST_SUITE(UnorderedPairs, StrictRead)

#include "testUnorderedPair/readerTests.hpp"

BOOST_AUTO_TEST_SUITE_END()

#include "testUnorderedPair/comparatorTests.hpp"
#include "testUnorderedPair/generatorTests.hpp"