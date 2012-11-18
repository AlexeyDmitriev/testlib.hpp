#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "testlib/testlib.hpp"
#include "testTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testFloat/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(Doubles, StrictRead)

#include "testFloat/allOk.hpp"
#include "testFloat/allFail.hpp"
#include "testFloat/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(NoStrictDoubles, NonStrictRead)

#include "testFloat/allOk.hpp"
#include "testFloat/allFail.hpp"
#include "testFloat/strictFail.hpp"
 
 
BOOST_AUTO_TEST_SUITE_END()

