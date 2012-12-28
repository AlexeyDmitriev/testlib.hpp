BOOST_AUTO_TEST_CASE(NothingToRead){
	setStr("");
	BOOST_CHECK_THROW(stream.read<string>(), VerdictException);
	
	setStr(" \n");
	BOOST_CHECK_THROW(stream.read<string>(), VerdictException);
}

BOOST_AUTO_TEST_CASE(WrongLength){
	setStr("test");
	BOOST_CHECK_THROW(stream.read<string>(3), VerdictException);
	
	setStr("dfnosdngfg");
	BOOST_CHECK_THROW(stream.read<string>(1), VerdictException);
}

BOOST_AUTO_TEST_CASE(LineFeed){
	setStr("mac style\r");
	BOOST_CHECK_THROW(stream.read<Line>(), VerdictException);
	
#ifdef ON_WINDOWS
	setStr("nix-style\n");
	BOOST_CHECK_THROW(stream.read<Line>(), VerdictException);
#endif
}

BOOST_AUTO_TEST_CASE(TooLong){
	setStr("too long\n");
	BOOST_CHECK_THROW(stream.read<Line>(7), VerdictException);
}