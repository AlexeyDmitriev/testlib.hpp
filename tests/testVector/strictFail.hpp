BOOST_AUTO_TEST_CASE(numberElementsStrict){
	setStr("0");
	vi res = {};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(), res);
	setStr("3 12 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(DefaultReader<int>()), res);
	
}

BOOST_AUTO_TEST_CASE(vectorNumElemStrict){		
	setStr("12 10\t\n1"); 
	vi res = {12, 10, 1};
	size_t q = 3;
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(q), res);
	setStr("12  -1"); 
	res = {12, -1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(2), res);
	
}

BOOST_AUTO_TEST_CASE(vectorNumElemSeparatorStrict){
	setStr("12 \t 10 1");
	typedef vector<long long> vll;
	vll res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vll>(3, sepSpace), res);
	setStr("12 \t 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vll>(3, sepSpace, DefaultReader<long long>()), res);
}

BOOST_AUTO_TEST_CASE(vectorEmptyStrict){
	setStr("2 12 -1");
	vi res = {12, -1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(), res);	
	
	setStr("3 12 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(DefaultReader<int>()), res);
}


BOOST_AUTO_TEST_CASE(vectorSeparatorStrict){	
	setStr("3\t \t 12 10 1");
	vi res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(sepTab, sepSpace), res);
	setStr("3\t 12  10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(sepTab, sepSpace), res);
}