#pragma once
#include "testlib/istream.hpp"
#include <sstream>
#include <string>

struct NonStrictRead {
	std::stringstream ss;
	IStream stream;
	
	NonStrictRead(): stream(ss, false) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};

struct StrictRead {
	std::stringstream ss;
	IStream stream;
	
	StrictRead(): stream(ss, true) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};
