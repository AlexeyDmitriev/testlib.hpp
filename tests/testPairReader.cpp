#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/readers/pair.hpp"
#include "testlib/readers/int.hpp"
#include "testlib/readers/float.hpp"
#include "testReadTools.hpp"
#include "testlib/readerWrapper.hpp"
#include "testPair/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(Pairs, StrictRead)


#include "testPair/allOk.hpp"
#include "testPair/allFail.hpp"
#include "testPair/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(NoStrictPairs, NonStrictRead)

#include "testPair/allOk.hpp"
#include "testPair/allFail.hpp"
#include "testPair/strictFail.hpp"
  
BOOST_AUTO_TEST_SUITE_END()
