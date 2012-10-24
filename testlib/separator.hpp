#pragma once
#include <string>

class Separator{
private:
	std::string separator;
public:
	/*implicit*/ Separator(char c): separator(1, c){}
	/*implicit*/ Separator(const char* s): separator(s){}
	/*implicit*/ Separator(const std::string& s): separator(s){}
	void read(IStream& stream) const {
		for(char c: separator){
			stream.readChar(c);
		}
	}
};
