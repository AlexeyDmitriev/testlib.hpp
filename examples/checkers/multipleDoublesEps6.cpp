#include "testlib.hpp"
using namespace std;

const double EPS = 1e-6;

TESTLIB_CHECK(){
	multipleDoublesEpsCheck(ans, ouf, EPS);
}
