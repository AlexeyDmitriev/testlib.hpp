BOOST_AUTO_TEST_CASE(numberElementsThrow){
	setStr("1.0 1.0");
	BOOST_CHECK_THROW(stream.read<vd>(), VerdictException);
	
	setStr("-1");
	vi res = {-1};
	BOOST_CHECK_THROW(stream.read<vi>(), VerdictException);
}

BOOST_AUTO_TEST_CASE(vectorNumElemThrow){		
	setStr("12 10 1k"); //+
	vi res = {12, 10, 1};
	size_t q = 3;
	BOOST_CHECK_THROW(stream.read<vi>(q), VerdictException); 
	
	setStr("p12 10 1"); //+
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(q, DefaultReader<int>()), VerdictException);
}

BOOST_AUTO_TEST_CASE(vectorNumElemSeparatorThrow){
	setStr("12\t10 1"); //+
	vi res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>(3, sepSpace), VerdictException);
	
	setStr("12 10\n1"); //+
	res = {12, 10, 1};
	BOOST_CHECK_THROW(stream.read<vi>((long long)(3), sepSpace, DefaultReader<int>()), VerdictException);	
}

BOOST_AUTO_TEST_CASE(vectorEmptyThrow){
	setStr("2vs12 -1"); //+
	vi res = {12, -1};
	BOOST_CHECK_THROW(stream.read<vi>(), VerdictException);
	
	setStr("3 12 10teorver1"); //+
	res = {3, 12, 10};
	BOOST_CHECK_THROW(stream.read<vi>(DefaultReader<int>()), VerdictException);
}


BOOST_AUTO_TEST_CASE(vectorSeparatorThrow){	
	vi res = {12, -1};
	setStr("2\n12 -1"); //+
	BOOST_CHECK_THROW(stream.read<vi>(sepTab, sepSpace), VerdictException);
	res = {12, 10, -1};
	setStr("3\n12 10 1"); //+
	BOOST_CHECK_THROW(stream.read<vi>(sepTab, sepSpace, DefaultReader<int>()), VerdictException);
}
