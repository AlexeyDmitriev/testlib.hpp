BOOST_AUTO_TEST_CASE(wrongLetters){
	setStr("string");
	
	BOOST_CHECK_THROW(stream.read<char>("name"), VerdictException);
}