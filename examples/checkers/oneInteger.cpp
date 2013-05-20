#include "testlib.hpp"
using namespace std;

TESTLIB_CHECK(){
	int expected = ans.read<int>();
	int received = ouf.read<int>();
	verifyEqual(expected, received);
	OK(received);
}
