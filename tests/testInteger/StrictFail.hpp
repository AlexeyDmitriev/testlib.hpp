#define MODE_CHECK_EQUAL(mode, a, b) \
	if (mode == IStream::Mode::NON_STRICT) \
		BOOST_CHECK_EQUAL(a, b); \
	else \
		BOOST_CHECK_THROW(a, ReadingException);


BOOST_AUTO_TEST_CASE(RandomInts1) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<int>(), 42);
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<int>(), 17);
}
