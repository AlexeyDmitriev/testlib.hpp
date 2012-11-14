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


BOOST_FIXTURE_TEST_SUITE(NoStrictIntegers, NonStrictRead)

#include "testInteger/allOk.hpp"
#include "testInteger/allFail.hpp"
#include "testInteger/StrictFail.hpp"
 
 
BOOST_AUTO_TEST_SUITE_END()
 