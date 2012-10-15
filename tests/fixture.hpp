#pragma once
#include "testlib/istream.hpp"
#include <sstream>
#include <string>

struct NonStrictRead {
	std::stringstream ss;
	IStream stream;
	
	NonStrictRead(): stream(ss, IStream::Mode::NON_STRICT) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};

struct StrictRead {
	std::stringstream ss;
	IStream stream;
	
	StrictRead(): stream(ss, IStream::Mode::STRICT) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};
