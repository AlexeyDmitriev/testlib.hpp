BOOST_AUTO_TEST_CASE(eofStrict) {	
	setStr(" \n");
	MODE_CHECK_THROW(stream.getMode(), stream.readEof());
		
	setStr(" \n\t\n");
	MODE_CHECK(stream.getMode(), stream.seekEof(), true, false);
	
	setStr("\n");
	MODE_CHECK(stream.getMode(), stream.seekEof(), true, false);
	
	setStr("4\n");
	BOOST_CHECK_EQUAL(stream.read<int>(), 4);
	MODE_CHECK(stream.getMode(), stream.seekEof(), true, false);
	
	setStr("\t");
	MODE_CHECK(stream.getMode(), stream.seekEof(), true, false);
	
	setStr("\t");
	MODE_CHECK_THROW(stream.getMode(), stream.readEof()); 
}

BOOST_AUTO_TEST_CASE(eolnStrict) {
	setStr(" \t " LINE_SEPARATOR "petr_is_cool_programmer");
	MODE_CHECK(stream.getMode(), stream.seekEoln(), true, false);
	
	setStr(" \t" LINE_SEPARATOR " p  ");
	MODE_CHECK(stream.getMode(), stream.seekEoln(), true, false);
}


BOOST_AUTO_TEST_CASE(charsStrict) {	
	setStr(" a bq");
	MODE_CHECK_THROW(stream.getMode(), stream.readChar('a'));
}


BOOST_AUTO_TEST_CASE(tokensStrict){
	setStr("token list");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "list");
	
	setStr("\ntoken");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "token");
}


BOOST_AUTO_TEST_CASE(spacesStrict){
	setStr("\n0");
	MODE_CHECK(stream.getMode(), stream.readChar(), '0', '\n');
}
