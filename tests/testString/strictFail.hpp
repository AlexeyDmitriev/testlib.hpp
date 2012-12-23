BOOST_AUTO_TEST_CASE(Spaces) {
	setStr(" test");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<string>(), "test");
	
	setStr("\n\n\t  fsgjfg  \n");
	MODE_CHECK_THROW(stream.getMode(), stream.read<string>());
	
	setStr(" \n\tlen  \n\n");
	MODE_CHECK_THROW(stream.getMode(), stream.read<string>(3));
}

BOOST_AUTO_TEST_CASE(NoLineFeed) {
	setStr("line");
	MODE_CHECK_THROW(stream.getMode(), stream.read<Line>());
	
	setStr("\n\n\n");
	for(int i = 0; i < 3; ++i){
		BOOST_CHECK_EQUAL(stream.read<Line>(), "");
	}
	MODE_CHECK_THROW(stream.getMode(), stream.read<Line>());
	
#ifndef ON_WINDOWS
	// OK, reads to \r, found \n
	setStr("windows-style\r\n"); 
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<Line>(), "windows-style");
#endif
}