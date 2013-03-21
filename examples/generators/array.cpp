#include "testlib.hpp"

TESTLIB_GENERATE() {
	int n = atoi(args[0].c_str());
	std::cout << n << std::endl;
}
