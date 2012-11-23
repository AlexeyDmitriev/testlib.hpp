#pragma once
#include <sstream>
#include "core.hpp"
#define QUIT(verdict, msg) \
do { \
	std::stringstream ss; \
	ss << msg; \
	throw ReadingException(verdict, ss.str()); \
} \
while (false); \

#define OK(msg) QUIT(Verdict::OK, msg)
#define WA(msg) QUIT(Verdict::WA, msg)
#define FAIL(msg) QUIT(Verdict::FAIL, msg)
#define PE(msg) QUIT(Verdict::PE, msg)

#define ensure(condition) \
if(!(condition)) \
	FAIL("\"" #condition "\" on line "  << __LINE__ << " is false");
