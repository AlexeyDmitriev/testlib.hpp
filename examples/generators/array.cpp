#include "testlib.hpp"

TESTLIB_GENERATE() {
	int n = atoi(args[0].c_str());
	int max = atoi(args[1].c_str());
	std::cout << n << std::endl;
	std::cout << separated(rnd.next<std::vector<int>>(n, 1, max), ' ') << std::endl;
}
