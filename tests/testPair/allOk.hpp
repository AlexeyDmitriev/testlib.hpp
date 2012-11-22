BOOST_AUTO_TEST_CASE(pairSimple){
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<pi>(), make_pair(42, 17));
}

BOOST_AUTO_TEST_CASE(pairSeparator){
	setStr("123\n345");
	BOOST_CHECK_EQUAL(stream.read<pi>('\n'), make_pair(123, 345));
	
	setStr("123 vs345");
	BOOST_CHECK_EQUAL(stream.read<pi>(" vs"), make_pair(123, 345));
}

BOOST_AUTO_TEST_CASE(pair2Readers){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
		
	setStr("42 17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(any, upTo20));
}

BOOST_AUTO_TEST_CASE(pair2ReadersSeparator){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
		
	setStr("42\t17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(any, upTo20, '\t'));
	setStr("42 topcoder 17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(any, upTo20, " topcoder "));	
}

BOOST_AUTO_TEST_CASE(pairReader){
	setStr("142 117");
	BOOST_CHECK_NO_THROW(stream.read<pi>(make_default_reader<int>(100, 200)));
}

BOOST_AUTO_TEST_CASE(pairReaderSeparator){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
		
	setStr("42\t17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(any, '\t'));
	setStr("12 topcoder 17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(upTo20, " topcoder "));	
}

BOOST_AUTO_TEST_CASE(pairDifferentTypes){
	typedef pair<float, int> p_F_I;
	setStr("123.0 345");
	BOOST_CHECK_EQUAL(stream.read<p_F_I>(), make_pair(float(123.0), 345));
}
