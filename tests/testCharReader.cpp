#include "testReadTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testChar/utils.hpp"
#include "testlib/readers/char.hpp"

BOOST_FIXTURE_TEST_SUITE(Integers, StrictRead)

#include "testChar/allOk.hpp"
#include "testChar/allFail.hpp"
#include "testChar/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

		
BOOST_FIXTURE_TEST_SUITE(NoStrictIntegers, NonStrictRead)

#include "testChar/allOk.hpp"
#include "testChar/allFail.hpp"
#include "testChar/strictFail.hpp"
 
 
BOOST_AUTO_TEST_SUITE_END()
 
