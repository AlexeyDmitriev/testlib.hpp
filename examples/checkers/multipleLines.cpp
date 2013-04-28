#include "testlib.hpp"
#include <string>
using namespace std;
TESTLIB_CHECK(){

	size_t linesNumber = 0;
	LineReader lineReader;

	while (ans.peek() != EOF){
		std::string ansLine = ans.read<std::string>(lineReader);
		if (ansLine == "" && ans.peek() == EOF)
			break;

		std::string oufLine = ouf.read<std::string>(lineReader);
		++linesNumber;
		if(ansLine != oufLine){
			WA(expectation(ansLine, oufLine) << " in " << linesNumber << " element");
		}
	}

	OK("Correct answer, " << linesNumber << " lines");
}
