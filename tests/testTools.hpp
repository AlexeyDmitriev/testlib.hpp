#pragma once
#include "testlib/istream.hpp"
#include <sstream>
#include <string>

#define MODE_CHECK_EQUAL(mode, a, b) \
	if (mode == IStream::Mode::NON_STRICT) \
		BOOST_CHECK(a == b); \
	else \
		BOOST_CHECK_THROW(a, ReadingException);


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
	return stream << '(' << p.first << ',' << p.second << ')' << std::endl;
}
};
