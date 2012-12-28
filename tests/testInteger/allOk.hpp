BOOST_AUTO_TEST_CASE(RandomInts) {
	setStr("42 17");
	BOOST_CHECK_EQUAL(stream.read<int>(), 42);
	BOOST_CHECK_NO_THROW(stream.readSpace());
	BOOST_CHECK_EQUAL(stream.read<int>(), 17);
	
	
	setStr("-123 999");
	BOOST_CHECK_EQUAL(stream.read<int>(), -123);
	stream.readSpace();
	BOOST_CHECK_EQUAL(stream.read<int>(), 999);
}

BOOST_AUTO_TEST_CASE(Negative) {
	setStr("-517");
	BOOST_CHECK_EQUAL(stream.read<int>(), -517);

	setStr("-1");
	BOOST_CHECK_EQUAL(stream.read<int>(), -1);
}

BOOST_AUTO_TEST_CASE(Overflow)
{
	setStr("65535 65535");
	BOOST_CHECK_EQUAL(stream.read<int>(), 65535);
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<short>(), VerdictException);

	setStr("2147483647 -9223372036854775810");
	BOOST_CHECK_NO_THROW(stream.read<int>());
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<long long>(), VerdictException);

	setStr("9999999999999999999999999999999999999");
	BOOST_CHECK_THROW(stream.read<int>(), VerdictException);

	setStr("2000000000");
	BOOST_CHECK_NO_THROW(stream.read<int>());
}


BOOST_AUTO_TEST_CASE(Corners) {
	testCorners<int>(*this);
	testCorners<long long>(*this);
	testCorners<short>(*this);

	testCorners<unsigned int>(*this);
	testCorners<unsigned long long>(*this);
	testCorners<unsigned short>(*this);
}

BOOST_AUTO_TEST_CASE(HexCorners){
	testHexCorners<int>(*this);
	testHexCorners<long long>(*this);
	testHexCorners<short>(*this);

	testHexCorners<unsigned int>(*this);
	testHexCorners<unsigned long long>(*this);
	testHexCorners<unsigned short>(*this);
}

BOOST_AUTO_TEST_CASE(PairInts) {
	testHexPairs<int>(*this, -110, 50, -110, 50);
	testHexPairs<long long>(*this, -1e10, -1e10 + 100, -1e18 - 20, -1e18);
	testHexPairs<short>(*this, -110, 50, -110, 50);
			
	testHexPairs<unsigned int>(*this, 500, 550, 100000, 100050);
	testHexPairs<unsigned long long>(*this, 1e10, 1e10 + 100, 1e18 - 20, 1e18);
	testHexPairs<unsigned short>(*this, 110, 150, 110, 150);
}

BOOST_AUTO_TEST_CASE(CorrectCase){
	const int AB = 10 * 16 + 11;
	
	setStr("AB");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::UPPER)), AB);
	
	setStr("AB");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::BOTH)), AB);
	
	setStr("ab");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::LOWER)), AB);
	
	setStr("ab");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::BOTH)), AB);
	
	setStr("a");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::LOWER)), 10);
	
	setStr("b");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::BOTH)), 11);
	
	setStr("B");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::BOTH)), 11);
	
	setStr("B");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>(Case::UPPER)), 11);
	
	setStr("123");
	BOOST_CHECK_NO_THROW(stream.read<int>(HexReader<int>(Case::UPPER)));
	
	setStr("123");
	BOOST_CHECK_NO_THROW(stream.read<int>(HexReader<int>(Case::LOWER)));
	
	setStr("123");
	BOOST_CHECK_NO_THROW(stream.read<int>(HexReader<int>(Case::BOTH)));
}

BOOST_AUTO_TEST_CASE(ImplicitilyCorrectCase){
	const int AB = 10 * 16 + 11;
	setStr("ab");
	BOOST_CHECK_EQUAL(stream.read<int>(HexReader<int>()), AB);
}