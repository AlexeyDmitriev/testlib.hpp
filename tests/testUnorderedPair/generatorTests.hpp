BOOST_FIXTURE_TEST_SUITE(UnorderedPairsRandom, RandomTest)

BOOST_AUTO_TEST_CASE(simpleGenerate) {
  UniqueGenerator<std::vector<pi>> generator;
  auto pairs = generator.generate(rnd, 10);
  BOOST_CHECK(std::unique(pairs.begin(), pairs.end()) == pairs.end());
}

BOOST_AUTO_TEST_SUITE_END()