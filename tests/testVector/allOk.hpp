BOOST_AUTO_TEST_CASE(numberElements){
	setStr("1.0 1.0");
	BOOST_CHECK_THROW(stream.read<vd>(), ReadingException);
	
	setStr("-1");
	vi res = {-1};
	BOOST_CHECK_THROW(stream.read<vi>(), ReadingException);
	
	setStr("3\n12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(DefaultReader<int>()) == res);
}

BOOST_AUTO_TEST_CASE(testAllMethods){	
	vi res = {12, -1};
	setStr("2\t12 -1");
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace) == res);
	
	setStr("3\t12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace, DefaultReader<int>()) == res);
	
	setStr("3\t12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace, DefaultReader<int>()) == res);
		
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((unsigned int)(3), DefaultReader<int>()) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((unsigned int)(3), DefaultReader<int>()) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((long long)(3), sepSpace, DefaultReader<int>()) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((long long)(3), sepSpace, DefaultReader<int>()) == res);
}
