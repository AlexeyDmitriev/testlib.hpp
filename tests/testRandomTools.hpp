#pragma once
#include "testlib/generator.hpp"
#include "testlib/random.hpp"
struct RandomTest {
	Random rnd;
	RandomTest(): rnd(0xFACE){}
};

struct OnesGenerator: public Generator<int>{
	int generate(Random&){
		return 1;
	}
};
