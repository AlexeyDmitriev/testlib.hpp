#include "testlib/generatorWrapper.hpp"

BOOST_FIXTURE_TEST_SUITE(UnorderedPairsRandom, RandomTest)

BOOST_AUTO_TEST_CASE(simpleGenerate) {
  UniqueGenerator<std::vector<pi>> generator;
  const int N = 150;
  const int minNumber = -10;
  const int maxNumber = 10;
  auto intGenerator = make_generator(DefaultGenerator<int>(), minNumber, maxNumber);
  auto pairGenerator = make_generator(DefaultGenerator<pi>(), intGenerator);
  auto pairs = generator.generate(rnd, N, pairGenerator);
  
  BOOST_CHECK(std::unique(pairs.begin(), pairs.end()) == pairs.end());

  for (auto pair : pairs) {
    BOOST_CHECK(pair.first >= minNumber && pair.first <= maxNumber
              && pair.second >= minNumber && pair.second <= maxNumber);
  }
}

BOOST_AUTO_TEST_SUITE_END()