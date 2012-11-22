BOOST_AUTO_TEST_CASE(pairSimpleThrow){
	setStr("12 -1");
	BOOST_CHECK_THROW(stream.read<piu>(), ReadingException);
}

BOOST_AUTO_TEST_CASE(pairSeparatorThrow){
	setStr("123vs345");
	BOOST_CHECK_THROW(stream.read<pi>("vs"), ReadingException);
		
	setStr("123 vs 345");
	auto upTo20 = make_default_reader<int>(0, 20);
	BOOST_CHECK_THROW(stream.read<pi>(upTo20, upTo20, "vs"), ReadingException);
}

BOOST_AUTO_TEST_CASE(pair2ReadersThrow){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
			
	setStr("42 17");
	BOOST_CHECK_THROW(stream.read<pi>(upTo20, any), ReadingException);
}

BOOST_AUTO_TEST_CASE(pair2ReadersSeparatorThrow){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
		
	setStr("42\t17");
	BOOST_CHECK_THROW(stream.read<pi>(any, upTo20, '\n'), ReadingException);
	setStr("42 topcoder 27");
	BOOST_CHECK_THROW(stream.read<pi>(any, upTo20, " topcoder"), ReadingException);	
}

BOOST_AUTO_TEST_CASE(pairReaderThrow){
	setStr("123 456");
	BOOST_CHECK_THROW(stream.read<pi>(make_default_reader<int>(100, 200)), ReadingException);
}

BOOST_AUTO_TEST_CASE(pairReaderSeparatorThrow){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
		
	setStr("42\t17");
	BOOST_CHECK_THROW(stream.read<pi>(any, '\n'), ReadingException);
	setStr("12 topcoder 27");
	BOOST_CHECK_THROW(stream.read<pi>(upTo20, " topcoder "), ReadingException);	
}

BOOST_AUTO_TEST_CASE(pairDifferentTypesThrow){
	typedef pair<unsigned int, int> p_UI_I;
	setStr("-123\n345");
	BOOST_CHECK_THROW(stream.read<p_UI_I>(), ReadingException);

	setStr("-123\n345");
	BOOST_CHECK_THROW(stream.read<p_UI_I>(), ReadingException);

	typedef pair<int, double> p_I_D;
	setStr("-123.0\n345");
	BOOST_CHECK_THROW(stream.read<p_I_D>(), ReadingException);
}
