BOOST_AUTO_TEST_CASE(numberElementsStrict){
	setStr("0");
	vi res = {};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(), res);
	setStr("3 12 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(DefaultReader<int>()), res);
	
}

BOOST_AUTO_TEST_CASE(testAllMethodsStrict){
	setStr("2 12 -1");
	vi res = {12, -1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(), res);	
	
	setStr("3 12 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(DefaultReader<int>()), res);
	
	setStr("12 10\t\n1");
	res = {12, 10, 1};
	size_t q = 3;
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(q), res);

	setStr("12 \t 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(3, sepSpace), res);
	
	setStr("12 10\t\n1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(q), res);
	
	setStr("12 \t 10 1");
	res = {12, 10, 1};
	MODE_CHECK_EQUAL(stream.getMode(), stream.read<vi>(3, sepSpace), res);
}
