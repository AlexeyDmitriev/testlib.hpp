BOOST_AUTO_TEST_CASE(SimpleString){
	setStr("two words");
	BOOST_CHECK_EQUAL(stream.read<string>(), "two");
	
	setStr("oneWord");
	BOOST_CHECK_EQUAL(stream.read<string>(), "oneWord");
}

BOOST_AUTO_TEST_CASE(CorrectLength){
	
	setStr("test with argument");
	BOOST_CHECK_EQUAL(stream.read<string>(10), "test");
	
	setStr("exact len");
	BOOST_CHECK_EQUAL(stream.read<string>(5), "exact");
}

BOOST_AUTO_TEST_CASE(Lines){
	setStr("oneWord\n");
	BOOST_CHECK_EQUAL(stream.read<Line>(),"oneWord");
	
	setStr("two words\n");
	BOOST_CHECK_EQUAL(stream.read<Line>(),"two words");
	
	setStr("  with \t spaces \t\t \n");
	BOOST_CHECK_EQUAL(stream.read<Line>(),"  with \t spaces \t\t ");
	
	setStr("exact length\n");
	BOOST_CHECK_NO_THROW(stream.read<Line>(12));
	
	setStr("short line\nand a lot of text after that");
	BOOST_CHECK_NO_THROW(stream.read<Line>(15));
}