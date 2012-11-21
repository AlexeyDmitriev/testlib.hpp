BOOST_AUTO_TEST_CASE(CornersThrow) {
	testCornersThrow<int>(*this);
	testCornersThrow<long long>(*this);
	testCornersThrow<short>(*this);

	testCornersThrow<unsigned int>(*this);
	testCornersThrow<unsigned long long>(*this);
	testCornersThrow<unsigned short>(*this);
}

BOOST_AUTO_TEST_CASE(BadFormat) {
	std::vector<std::string> strings = {
		"--1",
		"+1",
		"1-2",
		"za",
		"123a123",
		"01",
		"-0",
		"-12a6",
		"-a1",
		"-9a9",
		"-01",
		"00",
		"0.0",
		"30.",
		"-.0",
		"-.2",
		"-2.0",
		".1",
		"2.2"
	};

	for(const auto& s: strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<int>(), ReadingException);
	}

}

BOOST_AUTO_TEST_CASE(NegativeThrow) {
	setStr("");
	BOOST_CHECK_THROW(stream.read<int>(), ReadingException);
	setStr("-1");
	BOOST_CHECK_THROW(stream.read<unsigned>(), ReadingException);
}

BOOST_AUTO_TEST_CASE(HexBadFormat) {
	std::vector<std::string> strings = {
		"--1",
		"+1",
		"1-2",
		"za",
		"123a123",
		"01",
		"-0",
		"-12g6",
		"-a1F",
		"-9Aa9",
		"-01",
		"00",
		"0.0",
		"30.",
		"-.0",
		"-.2",
		"-2.0",
		".1",
		"2.2"
	};
 
	for(const auto& s: strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<int>(), ReadingException);
	}
}

BOOST_AUTO_TEST_CASE(HexBadSymbols) { 
	for (int i = -200; i < 1000; i++) {
		std::string res;
		int c = abs(i);
		bool good = true;
		while (c) {
			if (c % 36 >= 10) {
				res += char('a' + c % 36 - 10);
				if (c % 36 >= 16)
					good = false;
 
			}
			else
				res += char('0' + c % 36);
			c /= 36;
 
		}
		std::reverse(res.begin(), res.end());
		if (i < 0)
			res = "-" + res;
		if (i == 0)
			res = "0";
		setStr(res);
		if (!good) {
			BOOST_CHECK_THROW(HexReader<int>().read(stream), ReadingException);
		}
	}
}

BOOST_AUTO_TEST_CASE(HexCornersThrow)
{
	testHexCornersThrow<int>(*this);
	testHexCornersThrow<long long>(*this);
	testHexCornersThrow<short>(*this);

	testHexCornersThrow<unsigned int>(*this);
	testHexCornersThrow<unsigned long long>(*this);
	testHexCornersThrow<unsigned short>(*this);
}
