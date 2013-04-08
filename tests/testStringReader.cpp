#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "testlib/readers/string.hpp"
#include "testlib/alias.hpp"
#include "testReadTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testString/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(StrictString, StrictRead)

#include "testString/allOk.hpp"
#include "testString/allFail.hpp"
#include "testString/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

		
BOOST_FIXTURE_TEST_SUITE(NonStrictStrings, NonStrictRead)

#include "testString/allOk.hpp"
#include "testString/allFail.hpp"
#include "testString/strictFail.hpp"
 
 
BOOST_AUTO_TEST_SUITE_END()
 
