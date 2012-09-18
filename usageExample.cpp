#include "testlib/testlib.hpp"
#include <iostream>
int main(){
	IStream stream(std::cin);
	std::cout<<stream.read<int>()<<std::endl;  
	stream.readSpace();
	std::cout<<stream.read<int>(DefaultReader<int>(), 5, 17)<<std::endl;
	return 0; 
}  