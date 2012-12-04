#pragma once


#include <cstdlib>
#include <stdexcept>
#include <string>
#include <cassert>
#include <map>

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
	#define ON_WINDOWS
#endif


enum class Verdict{
	OK,
	FAIL,
	WA,
	PE
};

inline std::string shortMessage(Verdict verdict){
	switch(verdict){
		case Verdict::OK:
			return "OK";
		case Verdict::WA:
			return "Wrong answer";
		case Verdict::FAIL:
			return "FAIL";
		case Verdict::PE:
			return "Wrong output format";
		default:
			assert(false);
	}
}

inline std::string outcome(Verdict verdict){
	switch(verdict){
		case Verdict::OK:
			return "accepted";
		case Verdict::WA:
			return "wrong-answer";
		case Verdict::FAIL:
			return "fail";
		case Verdict::PE:
			return "presentation-error";
		default:
			assert(false);
	}
}

class VerdictException : std::exception {
public:
	Verdict verdict;
	std::string message;
	VerdictException(Verdict verdict, const std::string& str): verdict(verdict), message(str){}
};
