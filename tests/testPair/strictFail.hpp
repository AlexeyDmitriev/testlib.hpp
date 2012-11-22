BOOST_AUTO_TEST_CASE(separators){
	auto upTo20 = make_default_reader<int>(0, 20);
	auto any = make_default_reader<int>();
	setStr("42 topcoder 17");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>(any, upTo20, " topcoder"), make_pair(42, 17));	

	setStr("123\n345");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>(), make_pair(123, 345));	
	
	setStr("123 vs345");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>("vs"), make_pair(123, 345));

	typedef pair<long long, float> p_L_F;
	setStr("-123 --345.0");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<p_L_F>("-"), make_pair((long long)(-123), float(-345.0)));
	
	typedef pair<short, double> p_S_D;
	setStr("-123 -345.0");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<p_S_D>("-"), make_pair(short(-123), 345.0));

}
