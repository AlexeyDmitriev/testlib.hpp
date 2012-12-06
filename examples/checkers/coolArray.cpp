#include "testlib.hpp"
#include <vector>

using namespace std;
TESTLIB_CHECK(){
	int n = inf.read<int>();
	int l = inf.read<int>();
	int r = inf.read<int>();
	int s = inf.read<int>();
	vector<int> out = ouf.read<vector<int> >(n, make_default_reader<int>(l, r));
	long long sumSq = 0;
	for (auto i : out)
		sumSq += i * (long long)(i);
	if (sumSq % n != 0)
		WA("Sum of squares must divide on n");
	if (s * s * n != sumSq){
		WA("Sum of squares isn't equal to " << s);
	}
	else {
		OK(s);
	}
}
