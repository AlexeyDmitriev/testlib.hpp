#pragma once
#include "testlib/istream.hpp"
#include <sstream>
#include <string>
struct SimpleRead {
	std::stringstream ss;
	IStream stream;
	
	SimpleRead(): stream(ss) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};
