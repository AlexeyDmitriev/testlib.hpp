BOOST_AUTO_TEST_CASE(separators){
	setStr("123\n345");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>(), std::make_pair(123, 345));	
	
	setStr("123 vs345");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<pi>("vs"), std::make_pair(123, 345));

	typedef pair<long long, float> p_L_F;
	setStr("-123 --345.0");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<p_L_F>("-"), std::make_pair((long long)(-123), float(-345.0)));
	
	typedef pair<short, double> p_S_D;
	setStr("-123 -345.0");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<p_S_D>("-"), std::make_pair(short(-123), 345.0));

}
