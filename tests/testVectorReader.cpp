#include <boost/test/unit_test.hpp>
#include <iostream>
#include <utility>
#include <string>
#include "testlib/vector.hpp"
#include "testlib/int.hpp"
#include "testlib/float.hpp"
#include "testTools.hpp"
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

