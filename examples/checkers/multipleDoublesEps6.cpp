#include "testlib.hpp"
using namespace std;

const double EPS = 1e-6;

TESTLIB_CHECK(){
	AreEqualChecker<double, areCloseComparator<double>> checker{areCloseComparator<double> (EPS)};
	checkToEof<double>(ans, ouf, checker);
}
