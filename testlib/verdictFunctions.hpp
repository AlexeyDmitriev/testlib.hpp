#pragma once
#include <sstream>
#include <algorithm>
#include "core.hpp"
#include "utility.hpp"
#define QUIT(verdict, msg) \
do { \
	std::stringstream ss; \
	ss << msg; \
	throw VerdictException(verdict, ss.str()); \
} \
while (false); \

#define OK(msg) QUIT(Verdict::OK, msg)
#define WA(msg) QUIT(Verdict::WA, msg)
#define FAIL(msg) QUIT(Verdict::FAIL, msg)
#define PE(msg) QUIT(Verdict::PE, msg)

#define ensure(condition) \
if(!(condition)) {\
	FAIL("\"" #condition "\" on line "  << __LINE__ << " is false"); \
}

#define verify(condition, verdict, message) \
if(!(condition)) {\
	QUIT(verdict, message); \
}

template <typename T, typename U>
inline void verifyEqual(T&& t, U&& u, Verdict verdict = Verdict::WA){
	verify(t == u, verdict, t << " != " << u);
}

template <typename T>
inline void verifySorted(T start, T end, Verdict verdict = Verdict::WA){
	verify(std::is_sorted(start, end), verdict, expectation("Sorted range", rangeToString(start, end)));
}
