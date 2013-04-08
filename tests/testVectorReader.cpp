#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/readers/vector.hpp"
#include "testlib/readers/int.hpp"
#include "testlib/readers/float.hpp"
#include "testReadTools.hpp"
#include "testlib/readerWrapper.hpp"
#include <vector>
#include "testVector/utils.hpp"

BOOST_FIXTURE_TEST_SUITE(Vector, NonStrictRead)

#include "testVector/allOk.hpp"
#include "testVector/allFail.hpp"
#include "testVector/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(StrictVector, StrictRead)

#include "testVector/allOk.hpp"
#include "testVector/allFail.hpp"
#include "testVector/strictFail.hpp"

BOOST_AUTO_TEST_SUITE_END()

