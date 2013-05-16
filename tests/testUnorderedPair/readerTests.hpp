BOOST_AUTO_TEST_CASE(unorderedPairSimpleThrow) {
  setStr("12 a");
  BOOST_CHECK_THROW(stream.read<pi>(), VerdictException);
}

BOOST_AUTO_TEST_CASE(unorderedPairSimple) {
  setStr("42 17");
  BOOST_CHECK_EQUAL(stream.read<pi>(), pi(42, 17));

  setStr("17 42");
  BOOST_CHECK_EQUAL(stream.read<pi>(), pi(42, 17));
}

BOOST_AUTO_TEST_CASE(separators) {
  auto upTo20 = make_default_reader<int>(0, 20);
  auto any = make_default_reader<int>();
  setStr("42 topcoder 17");
  MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>(any, upTo20, " topcoder"), pi(42, 17));  

  setStr("123\n345");
  MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>(), pi(123, 345));  
  
  setStr("123 vs345");
  MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>("vs"), pi(123, 345));
}
