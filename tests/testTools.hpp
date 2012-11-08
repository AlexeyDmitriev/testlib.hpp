#pragma once
#include "testlib/istream.hpp"
#include <sstream>
#include <string>

inline int rnd()
{
	static int RND_X = 0;
	RND_X = RND_X * 26 + 17;
	return RND_X;
}

struct NonStrictRead {
	std::stringstream ss;
	OutputIStream stream;
	
	NonStrictRead(): stream(ss, IStream::Mode::NON_STRICT) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};

struct StrictRead {
	std::stringstream ss;
	OutputIStream stream;
	
	StrictRead(): stream(ss, IStream::Mode::STRICT) {}
	void setStr(const std::string& s){
		ss.clear();
		ss.str(s);
	}
};

namespace std {
template<typename T, typename U>
std::ostream& operator << (std::ostream& stream, pair<T, U> const & p){
	return stream << '(' << p.first << ',' << p.second;
}
};
