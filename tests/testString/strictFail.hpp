BOOST_AUTO_TEST_CASE(Spaces) {
	setStr(" test");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<string>(), "test");
	
	setStr("\n\n\t  fsgjfg  \n");
	MODE_CHECK_THROW(stream.getMode(), stream.read<string>());
	
	setStr(" \n\tlen  \n\n");
	MODE_CHECK_THROW(stream.getMode(), stream.read<string>(3));
}