#include "testlib/testlib.hpp"
#include <iostream>
int main(){
	try{
		IStream stream(std::cin);
		std::cout<<stream.read<int>()<<std::endl;  
		stream.readSpace();
		std::cout<<stream.read<int>(DefaultReader<int>(), 5, 17)<<std::endl;
	}
	catch(ReadingException e){
		quit(e.verdict, e.str);
	}
	return 0; 
}  