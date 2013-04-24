BOOST_AUTO_TEST_CASE(pairSimple){
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<pi>(), pi(42, 17));
}
