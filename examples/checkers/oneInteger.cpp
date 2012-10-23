#include "testlib/testlib.hpp"
#include "testlib/macro.hpp"
using namespace std;
TESTLIB_CHECK(){
	(void)inf;
	int a = ans.read<int>();
	int b = ouf.read<int>();
	if(a != b){
		WA(expectation(a, b));
	}
	else {
		OK(to_string(a));
	}
}
