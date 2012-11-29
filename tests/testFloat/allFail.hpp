BOOST_AUTO_TEST_CASE(BadFormatMinuses) {
	std::vector<std::string> strings = {
		"--1",
		"+-1",
		"1-2",
		"za",
		"123+a123",
		"-+01",
		"-12a6",
		"-a.1",
		"-99.a",
		"-01",
		"0+0"
	};

	for (const auto& s : strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<double>(), VerdictException);
	}

}

BOOST_AUTO_TEST_CASE(BadFormatTooManyPoints) {
	std::vector<std::string> strings = {
		"-1.0000.",
		"+0..000",
		".2",
		"123.12.3",
		".1",
		"-.0",
		"-.17",
		"-1.",
	};

	for (const auto& s : strings) {
		setStr(s);\
		BOOST_CHECK_THROW(stream.read<double>(), VerdictException);
	}

}

BOOST_AUTO_TEST_CASE(WrongNumbersSize) {
	std::string curString(1000, '1');

	setStr(curString);
	BOOST_CHECK_THROW(stream.read<double>(), VerdictException);
}

BOOST_AUTO_TEST_CASE(NormalWorkingWithSpacesThrow){	
	setStr("-517.\n");
	BOOST_CHECK_THROW(stream.read<double>(), VerdictException);
}


BOOST_AUTO_TEST_CASE(DoubleCheckInRangeThrow) {
	for(int i = 9000; i < 9300; i+= 23){
		double l = i / 1000.0;
		double r = r + 0.2;
		for (double m = l - 0.1; m <= r + 0.1; m += 0.07){
			setStr(toString(m));
			if (!(l < m - 1e-10 && m + 1e-10 < r))
			{
				BOOST_CHECK_THROW(stream.read<double>(l, r), VerdictException);
			}
		}
	}
}

BOOST_AUTO_TEST_CASE(IncorrectSymbols) {
	std::vector<std::string> strings = {
		"za",
		"-12a6.0",
		"-a.1",
		"-9a.9",
	};

	for (const auto& s : strings) {
		setStr(s);
		BOOST_CHECK_THROW(stream.read<double>(), VerdictException);
	}

}