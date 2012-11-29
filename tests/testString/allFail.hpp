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