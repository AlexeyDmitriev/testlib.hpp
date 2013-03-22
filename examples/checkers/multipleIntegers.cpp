#include "testlib.hpp"
using namespace std;

TESTLIB_CHECK(){

	size_t integersNumber = 0;
	while (!ans.seekEof() && !ouf.seekEof()){
		int a = ans.read<int>();
		int b = ouf.read<int>();
		++integersNumber;
		if(a != b){
			WA(expectation(a, b) << " in " << integersNumber << " element");
		}
	}
	
	checkExtraTokensInEnd<int>(ans, ouf, integersNumber);
	OK("Correct answer, " << integersNumber << " numbers");
}
