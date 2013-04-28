#include "testlib.hpp"
using namespace std;

bool isNumeric(const string& number) {

	if (number.empty()) {
		return false;
	}

	if (number.length() == 1) {
		return isdigit(number[0]);
	}

	bool isSigned = (number[0] == '+' || number[0] == '-');
	if (isSigned) {
		if (number[0] == '-' && number[1] == '0') {
			return false;
		}
	}
	
	size_t startIndex = isSigned ? 1 : 0;
	if ((number[startIndex] == '0') && (startIndex + 1 < number.length())) {
		return false;
	}

	for (size_t i = startIndex; i < number.length(); ++i) {
		if (!isdigit(number[i])) {
			return false;
		}
	}
	return true;
}

string readNumber(IStream& stream) {
	string number = stream.read<string>();
	if (!isNumeric(number)) {
		stream.quit(Verdict::PE, expectation("Integer", number));
	}
	if (number.front() == '+') {
		number.erase(number.begin());
	}
	return number;
}

TESTLIB_CHECK(){
	string expected = readNumber(ans);
	string received = readNumber(ouf);

	verifyEqual(expected, received);
	OK(received);
}
