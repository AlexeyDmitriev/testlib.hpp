BOOST_AUTO_TEST_CASE( eof ) {	
	setStr("");
	BOOST_CHECK_NO_THROW(stream.readEof());
	
//	setStr(" \n");
//	BOOST_CHECK_NO_THROW(stream.readEof());
	
	setStr(" lekha\n");
	BOOST_CHECK_THROW(stream.readEof(), ReadingException);
	
	setStr(" \npetr_is_cool_programmer");
	BOOST_CHECK_EQUAL(stream.seekEof(), false);
	
//	setStr(" \n\t\n");
//	BOOST_CHECK_EQUAL(stream.seekEof(), true);
	
//	setStr("\n");
//	BOOST_CHECK_EQUAL(stream.seekEof(), true);
	
//	setStr("4\n");
//	BOOST_CHECK_NO_THROW(stream.read<int>());
//	BOOST_CHECK_EQUAL(stream.seekEof(), true);
}

BOOST_AUTO_TEST_CASE( eoln ) {
	
	
	setStr("");
	BOOST_CHECK_THROW(stream.readEoln(), ReadingException);
	
	setStr(" \n");
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readEoln());
	
//	setStr(" \t \npetr_is_cool_programmer");
//	BOOST_CHECK_EQUAL(stream.seekEoln(), true);
	
	setStr(" p\n    ");
	BOOST_CHECK_EQUAL(stream.seekEoln(), false);
//	setStr(" \t\n p  ");
//	BOOST_CHECK_EQUAL(stream.seekEoln(), true);
}

BOOST_AUTO_TEST_CASE( chars ) {
	setStr("a bq");
	BOOST_CHECK_EQUAL(stream.readChar(), 'a');
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_NO_THROW(stream.readChar('b'));
	BOOST_CHECK_THROW(stream.readChar('x'), ReadingException);
}

BOOST_AUTO_TEST_CASE( tokens ){
	BOOST_CHECK_THROW(stream.readToken(), ReadingException);
	
//	setStr("token list");
//	BOOST_CHECK_EQUAL(stream.readToken(), "token");
//	BOOST_CHECK_EQUAL(stream.readToken(), "list");
	
//	setStr("\ntoken");
//	BOOST_CHECK_EQUAL(stream.readToken(), "token");
	
	setStr("lekha\n");
	BOOST_CHECK_EQUAL(stream.readToken(), "lekha");
	BOOST_CHECK_NO_THROW(stream.readEoln());
	
}

BOOST_AUTO_TEST_CASE(superTest){
	setStr("3 3\naba p -3 1");
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