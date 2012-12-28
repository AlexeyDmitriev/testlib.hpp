BOOST_AUTO_TEST_CASE(eof) {	
	setStr("");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" ");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEof());

	setStr(" lekha\n");
	BOOST_CHECK_THROW(stream.readEof(), VerdictException);
	
	setStr(" \npetr_is_cool_programmer");
	BOOST_CHECK_EQUAL(stream.seekEof(), false);
}

BOOST_AUTO_TEST_CASE(eoln) {	
	setStr("");
	BOOST_CHECK_THROW(stream.readEoln(), VerdictException);
	
	setStr(" " LINE_SEPARATOR);
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEoln());

	setStr(" p\n    ");
	BOOST_CHECK_EQUAL(stream.seekEoln(), false);
	
	setStr(LINE_SEPARATOR);
	BOOST_CHECK_EQUAL(stream.seekEoln(), true);
	
	setStr("\t");
	BOOST_CHECK_EQUAL(stream.seekEoln(), false);
	
}

BOOST_AUTO_TEST_CASE( chars ) {
	setStr("a bq");
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), VerdictException);
}

BOOST_AUTO_TEST_CASE(tokens){
	BOOST_CHECK_THROW(stream.readToken(), VerdictException);
	
	setStr("token list");
	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.readToken(), "list");
	
	setStr("lekha" LINE_SEPARATOR);
	BOOST_CHECK_EQUAL(stream.readToken(), "lekha");
	BOOST_CHECK_NO_THROW(stream.readEoln());
	
}

BOOST_AUTO_TEST_CASE(superTest){
	setStr("3 3" LINE_SEPARATOR "aba p -3 1");
	BOOST_CHECK_EQUAL(stream.read<short>(), 3);
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.read<int>(), 3);
	BOOST_CHECK_NO_THROW(stream.readEoln());
	BOOST_CHECK_EQUAL(stream.readToken(), "aba");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.readChar(), 'p');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.read<double>(), -3);
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.read<int>(), 1);
}