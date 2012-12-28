BOOST_AUTO_TEST_CASE(RandomDouble) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<double>(), 42);

	setStr("-123.11 999.222 0.2");
	BOOST_CHECK_EQUAL(stream.read<double>(), -123.11);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<double>(), 999.222);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<double>(), 0.2);
}

BOOST_AUTO_TEST_CASE(NegativeDouble) {
	setStr("-517.512521");
	BOOST_CHECK_EQUAL(stream.read<double>(), -517.512521);

	setStr("-1");
	BOOST_CHECK_EQUAL(stream.read<double>(), -1);

	setStr("-0.0");
	BOOST_CHECK_EQUAL(stream.read<double>(), 0);
	
	setStr("-0");
	BOOST_CHECK_EQUAL(stream.read<double>(), 0);

	setStr("-0.21");
	BOOST_CHECK_EQUAL(stream.read<double>(), -0.21);
}

BOOST_AUTO_TEST_CASE(NormalWorkingWithSpaces){
	setStr("-517.512521 2.4990");
	BOOST_CHECK_EQUAL(stream.read<double>(), -517.512521);
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.read<double>(), 2.4990);

}

BOOST_AUTO_TEST_CASE(DoubleCheckInRange) {
	
	setStr("0.001");
	BOOST_CHECK_NO_THROW(stream.read<double>(0.001, 0.001));
	setStr("0.000");
	BOOST_CHECK_NO_THROW(stream.read<double>(0.000, 0.000));
	setStr("0.000");
	BOOST_CHECK_NO_THROW(stream.read<double>(-0.001, 0.001));
	
	for(int i = 9000; i < 9300; i+= 23){
		double l = i / 1000.0;
		double r = r + 0.2;
		for (double m = l - 0.1; m <= r + 0.1; m += 0.07){
			setStr(toString(m));
			if (l < m && m < r)
			{
				BOOST_CHECK_NO_THROW(stream.read<double>(l, r));
			}
		}
	}
}
