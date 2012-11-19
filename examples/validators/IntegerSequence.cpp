#include "testlib.hpp"

TESTLIB_VALIDATE(){
	int n = inf.read<int>(1, 5);
	inf.readEoln();
	for(int i = 0; i < n; ++i){
		if(i != 0)
			inf.readSpace();
		inf.read<int>(1, 9);
	}
	inf.readEoln();
}