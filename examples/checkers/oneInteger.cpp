#include "testlib.hpp"
using namespace std;
TESTLIB_CHECK(){
	int a = ans.read<int>();
	int b = ouf.read<int>();
	if(a != b){
		WA(expectation(a, b));
	}
	else{
		OK(a);
	}
}
