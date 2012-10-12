#include "testlib/testlib.hpp"
#include <iostream>
#include "testlib/readerWrapper.hpp"

int main() {
	try {
		IStream stream(std::cin);
		auto reader = make_reader(DefaultReader<int>(), 5, 17);
		std::cout << stream.read<int>(reader) << std::endl;
		stream.readSpace();
		std::cout << stream.read<int>() << std::endl;
	}	catch (ReadingException e) {
		quit(e.verdict, e.message);
	}
	return 0;
}
