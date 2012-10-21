#include "testlib/testlib.hpp"
#include "testlib/macro.hpp"
using namespace std;
TESTLIB_CHECK(){
	(void)inf;
	int a = ans.read<int>();
	int b = ouf.read<int>();
	if(a != b){
		throw ReadingException(Verdict::WA, expectation(a, b));
	}
	else {
		throw ReadingException(Verdict::OK, to_string(a));
	}
}
