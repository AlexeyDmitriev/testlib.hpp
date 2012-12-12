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
do { \
	if(!(condition)) {\
		FAIL("\"" #condition "\" on line "  << __LINE__ << " is false"); \
	} \
} while(false);

#define verify(condition, verdict, message) \
do { \
	if(!(condition)) {\
		QUIT(verdict, message); \
	} \
} while(false);

template <typename T, typename U>
inline void verifyEqual(T&& t, U&& u, Verdict verdict = Verdict::WA){
	verify(t == u, verdict, t << " != " << u);
}

template <typename T>
inline void verifySorted(T start, T end, Verdict verdict = Verdict::WA){
	verify(std::is_sorted(start, end), verdict, expectation("Sorted range", rangeToString(start, end)));
}

template <typename T, typename U>
inline void verifyEqualRanges (T startT, T endT, U startU, U endU, Verdict verdict = Verdict::WA){
	T itT = startT;
	U itU = startU;
	while(true){
		if(itT == endT && itU == endU)
			return;
		if(itT == endT || itU == endU)
			QUIT(verdict, rangeToString(startT, endT) << " != " << rangeToString(startU, endU));
		if(*itT != *itU)
			QUIT(verdict, rangeToString(startT, endT) << " != " << rangeToString(startU, endU));
		++itT;
		++itU;
	}
}
