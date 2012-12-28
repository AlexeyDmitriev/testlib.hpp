#include "testlib.hpp"
#include <vector>

using namespace std;
TESTLIB_CHECK(){
	long long n = inf.read<long long>();
	long long l = inf.read<long long>();
	long long r = inf.read<long long>();
	long long s = inf.read<long long>();
	vector<long long> out = ouf.read<vector<long long>>(n, make_default_reader<long long>(l, r));
	long long sumSq = 0;
	for (auto i : out)
		sumSq += i * i;
	if (sumSq % n != 0)
		WA("Sum of squares must be divided by n");
	if (s * s * n != sumSq){
		WA("Quadratic mean isn't equal to " << s);
	}
	OK ("Correct answer");
}
