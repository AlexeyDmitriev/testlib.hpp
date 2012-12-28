BOOST_AUTO_TEST_CASE(RandomDouble1) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<double>(), 42);
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<double>(), 17);
}