#include "testlib.hpp"

TESTLIB_GENERATE() {
	size_t n = args.get<size_t>();
	int max = args.get<int>();
	std::cout << n << std::endl;
	std::cout << separated(rnd.next<std::vector<int>>(n, 1, max), ' ') << std::endl;
}
