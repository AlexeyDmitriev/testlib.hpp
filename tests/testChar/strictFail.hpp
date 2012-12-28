BOOST_AUTO_TEST_CASE(skipBlanks){
	setStr(" space");
	MODE_CHECK_THROW(stream.getMode(), stream.read<char>("because"));
}