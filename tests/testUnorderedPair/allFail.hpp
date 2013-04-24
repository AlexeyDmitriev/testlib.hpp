BOOST_AUTO_TEST_CASE(pairSimpleThrow){
	setStr("12 a");
	BOOST_CHECK_THROW(stream.read<pi>(), VerdictException);
}

