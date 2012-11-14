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
	BOOST_CHECK_THROW(stream.read<short>(), ReadingException);

	setStr("2147483647 -9223372036854775810");
	BOOST_CHECK_NO_THROW(stream.read<int>());
	stream.readSpace();
	BOOST_CHECK_THROW(stream.read<long long>(), ReadingException);

	setStr("9999999999999999999999999999999999999");
	BOOST_CHECK_THROW(stream.read<int>(), ReadingException);

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

BOOST_AUTO_TEST_CASE(HexCase)
{
	setStr("FF");
	BOOST_CHECK_NO_THROW(HexReader<int>(Case::UPPER).read(stream));
}



BOOST_AUTO_TEST_CASE(PairInts) {
	testHexPairs<int>(*this, -110, 50, -110, 50);
	testHexPairs<long long>(*this, -1e10, -1e10 + 100, -1e18 - 20, -1e18);
	testHexPairs<short>(*this, -110, 50, -110, 50);
			
	testHexPairs<unsigned int>(*this, 500, 550, 100000, 100050);
	testHexPairs<unsigned long long>(*this, 1e10, 1e10 + 100, 1e18 - 20, 1e18);
	testHexPairs<unsigned short>(*this, 110, 150, 110, 150);
}
