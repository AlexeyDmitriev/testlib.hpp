BOOST_AUTO_TEST_CASE(SimpleString){
	setStr("two words");
	BOOST_CHECK_EQUAL(stream.read<string>(), "two");
	
	setStr("oneWord");
	BOOST_CHECK_EQUAL(stream.read<string>(), "oneWord");
}

BOOST_AUTO_TEST_CASE(CorrectLength){
	
	setStr("test with argument");
	BOOST_CHECK_EQUAL(stream.read<string>(10), "test");
	
	setStr("exact len");
	BOOST_CHECK_EQUAL(stream.read<string>(5), "exact");
}