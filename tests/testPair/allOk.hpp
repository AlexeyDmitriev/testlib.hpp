BOOST_AUTO_TEST_CASE(testRandom){
	setStr("12 -1");
	BOOST_CHECK_EQUAL(stream.read<pil>(), std::make_pair(12, -1LL));
}

BOOST_AUTO_TEST_CASE(customReaders){	
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
		
	setStr("42 17");
	BOOST_CHECK_NO_THROW(stream.read<pi>(any, upTo20));
	
	setStr("123 456");
	BOOST_CHECK_NO_THROW(stream.read<pi>(make_default_reader<int>(100, 1000)));
}

BOOST_AUTO_TEST_CASE(differentTypes){
	typedef pair<float, int> p_F_I;
	setStr("123.0 345");
	BOOST_CHECK_EQUAL(stream.read<p_F_I>(), std::make_pair(float(123.0), 345));
}

BOOST_AUTO_TEST_CASE(StrictSeparators){	
	setStr("123\n345");
	BOOST_CHECK_NO_THROW(stream.read<pi>('\n'));
	
	setStr("123 vs345");
	BOOST_CHECK_NO_THROW(stream.read<pi>(" vs"));
}