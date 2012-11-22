BOOST_AUTO_TEST_CASE(RandomInts1) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<int>(), 42);
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<int>(), 17);
}

BOOST_AUTO_TEST_CASE(DefaultCase){
	const int AB = 10 * 16 + 11;
	setStr("AB");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<int>(HexReader<int>()), AB);
	
	setStr("aB");
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<int>(HexReader<int>()), AB);
}