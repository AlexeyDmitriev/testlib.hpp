#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "testlib/readers/int.hpp"
#include "testReadTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testInteger/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(Integers, StrictRead)

#include "testInteger/allOk.hpp"
#include "testInteger/allFail.hpp"
#include "testInteger/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

		
BOOST_FIXTURE_TEST_SUITE(NoStrictIntegers, NonStrictRead)

#include "testInteger/allOk.hpp"
#include "testInteger/allFail.hpp"
#include "testInteger/strictFail.hpp"
 
 
BOOST_AUTO_TEST_SUITE_END()
 
