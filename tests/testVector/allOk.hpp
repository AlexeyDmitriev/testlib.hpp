BOOST_AUTO_TEST_CASE(numberElements){	
	setStr("3\n12 10 1");
	vi res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(DefaultReader<int>()) == res);
}

BOOST_AUTO_TEST_CASE(vectorNumElem){		
	setStr("2\n12 -1"); 
	vi res = {12, -1};
	BOOST_CHECK(stream.read<vi>() == res);
	
	setStr("2\n12 -1"); 
	res = {12, -1};
	BOOST_CHECK(stream.read<vi>(DefaultReader<int>()) == res);
}

BOOST_AUTO_TEST_CASE(vectorNumElemSeparator){
	setStr("2\t12 -1");
	vi res = {12, -1};
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace) == res);
	
	setStr("3\t12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>(sepTab, sepSpace, DefaultReader<int>()) == res);
}

BOOST_AUTO_TEST_CASE(vectorEmpty){
	vi res = {12, -1};
	setStr("12 -1"); //+
	BOOST_CHECK(stream.read<vi>(2) == res);
	
	setStr("12 10 1");
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((unsigned int)(3), DefaultReader<int>()) == res);
}


BOOST_AUTO_TEST_CASE(vectorSeparator){	
	setStr("12\t10\t1");
	vi res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((long long)(3), sepTab) == res);
	
	setStr("12 10 1"); 
	res = {12, 10, 1};
	BOOST_CHECK(stream.read<vi>((long long)(3), sepSpace, DefaultReader<int>()) == res);
}