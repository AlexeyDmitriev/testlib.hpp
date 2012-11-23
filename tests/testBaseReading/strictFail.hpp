BOOST_AUTO_TEST_CASE(charsStrict) {
}

BOOST_AUTO_TEST_CASE(tokensStrict){	
	setStr("token list");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "list");
	
	setStr("\ntoken");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "token");	
}



/*
BOOST_AUTO_TEST_CASE( eof ) {
	setStr("");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr("");
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
	
	setStr(" ");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" ");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);

	setStr("\t");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);

	setStr("\t");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEof(), false);
}

BOOST_AUTO_TEST_CASE( chars ) {
	setStr("a bq");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), ReadingException);
	
	setStr(" a bq");
	BOOST_CHECK_THROW(stream.readChar('a'), ReadingException);

	setStr("\ta ");
	BOOST_CHECK_NO_THROW(stream.readChar('\t'));
	MODE_CHECK_EQUAL(stream.getMode(), stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readChar(' '));
	BOOST_CHECK_THROW(stream.readChar('\n'), ReadingException);
	
	setStr("\na ");
	BOOST_CHECK_NO_THROW(stream.readChar('\n'));
	MODE_CHECK_EQUAL(stream.getMode(), stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readChar(' '));
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr("\t");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEoln(), false);
	setStr("\n");
	MODE_CHECK_EQUAL(stream.getMode(), stream.seekEoln(), true);
}

BOOST_AUTO_TEST_CASE( tokens ){
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	setStr("token list");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "token");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "list");
	
	setStr("\ntoken");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
	setStr("\t");
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
}

BOOST_AUTO_TEST_CASE(spaces){
	setStr("  \t\n");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readChar(), ' ');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
	
	setStr("\n0+0=1");
	BOOST_CHECK_THROW(stream.readSpace(), ReadingException);
	
	setStr("\n0+ 0= 1 ");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readChar(), '\n');
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "0+");
	MODE_CHECK_EQUAL(stream.getMode(), stream.readChar(), ' ');
	MODE_CHECK_EQUAL(stream.getMode(), stream.readToken(), "0=");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);
}
*/