BOOST_AUTO_TEST_CASE(correctLetters){
	setStr("string");
	
	BOOST_CHECK_EQUAL(stream.read<char>("s"), 's');
	BOOST_CHECK_EQUAL(stream.read<char>("tea"), 't');
	BOOST_CHECK_EQUAL(stream.read<char>("core"), 'r');
	BOOST_CHECK_EQUAL(stream.read<char>("string"), 'i');
	BOOST_CHECK_EQUAL(stream.read<char>("on"), 'n');
	BOOST_CHECK_EQUAL(stream.read<char>("g"), 'g');
	
}