#pragma once
#include "testlib/istream.hpp"
#include <sstream>
#include <string>

struct Read{
	OutputIStream stream;
	std::stringstream ss;
	Read(IStream::Mode m) : stream(ss, m) {} 
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};

struct NonStrictRead : public Read{
	NonStrictRead(): Read(IStream::Mode::NON_STRICT) {}
	
};

struct StrictRead : public Read{
	StrictRead(): Read(IStream::Mode::STRICT) {}
};

namespace std {
template<typename T, typename U>
std::ostream& operator << (std::ostream& stream, pair<T, U> const & p){
	return stream << '(' << p.first << ',' << p.second;
}
};
