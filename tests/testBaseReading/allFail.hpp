BOOST_AUTO_TEST_CASE(eofThrow) {
	setStr("");
	BOOST_CHECK_THROW(stream.readSpace(), VerdictException);
}

BOOST_AUTO_TEST_CASE(charsThrow) {
	setStr("a bq");
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), VerdictException);
	
	setStr("\ta ");
	BOOST_CHECK_NO_THROW(stream.readChar('\t'));
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readChar(' '));
	BOOST_CHECK_THROW(stream.readChar('\n'), VerdictException);
	
	setStr("\na ");
	BOOST_CHECK_NO_THROW(stream.readChar('\n'));
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readChar(' '));
	BOOST_CHECK_NO_THROW(stream.readEof());
	
}

BOOST_AUTO_TEST_CASE(tokensThrow){
	setStr("\t");
	BOOST_CHECK_THROW(stream.readToken(), VerdictException);
	
	setStr("\n");
	BOOST_CHECK_THROW(stream.readToken(), VerdictException);
	
	setStr("\r\n");
	BOOST_CHECK_THROW(stream.readToken(), VerdictException);
	
	setStr("");
	BOOST_CHECK_THROW(stream.readToken(), VerdictException);
}

BOOST_AUTO_TEST_CASE(spacesThrow){	
	setStr("\n0+0=1");
	BOOST_CHECK_THROW(stream.readSpace(), VerdictException);
	
}
