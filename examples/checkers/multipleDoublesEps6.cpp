#include "testlib.hpp"
using namespace std;

const double EPS = 1e-6;

TESTLIB_CHECK(){

	size_t doublesNumber = 0;
	while (!ans.seekEof() && !ouf.seekEof()){
		double ansDouble = ans.read<double>();
		double oufDouble = ouf.read<double>();
		++doublesNumber;

		if(!areClose(ansDouble, oufDouble, EPS)){
			WA(expectation(ansDouble, oufDouble) << ", error = " << ansDouble - oufDouble
				<< " in " << doublesNumber << " element");
		}
	}

	checkExtraTokensInEnd<double>(ans, ouf, doublesNumber);
	OK("Correct answer, " << doublesNumber << " numbers");
}
