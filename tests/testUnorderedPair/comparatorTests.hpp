BOOST_AUTO_TEST_CASE(equal) {
  BOOST_CHECK_EQUAL(pi(1, 2), pi(1, 2));
  BOOST_CHECK_EQUAL(pi(1, 2), pi(2, 1));
  BOOST_CHECK_EQUAL(ps("aba", "caba"), ps("caba", "aba"));
}

BOOST_AUTO_TEST_CASE(notEqual) {
  BOOST_CHECK(pi(1, 2) != pi(3, 4));

  BOOST_CHECK(pi(1, 2) != pi(1, 3));
  BOOST_CHECK(pi(2, 1) != pi(3, 1));
  
  BOOST_CHECK(pi(1, 2) != pi(3, 1));
  BOOST_CHECK(pi(2, 1) != pi(1, 3));
}

BOOST_AUTO_TEST_CASE(less) {
  BOOST_CHECK(pi(1, 2) < pi(1, 3)); 
  BOOST_CHECK(pi(1, 2) < pi(3, 1)); 
  BOOST_CHECK(ps("aaa", "bbb") < ps("ccc", "bbb"));
}
