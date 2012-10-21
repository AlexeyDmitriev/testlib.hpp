#pragma once


#include <cstdlib>
#include <stdexcept>
#include <string>
#include <cassert>
#include <map>

//TODO: proper OS choosing
#define ON_LINUX
//#define ON_WINDOWS


enum class Verdict{
	OK,
	FAIL,
	WA,
	PE
};

inline int exitCode(Verdict verdict){
	switch(verdict){
		case Verdict::OK:
			return 0;
		case Verdict::WA:
			return 1;
		case Verdict::FAIL:
			return 2;
		case Verdict::PE:
			return 3;
		default:
			assert(false);
	}
}

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

class ReadingException : std::exception {
public:
	Verdict verdict;
	std::string message;
	ReadingException(Verdict verdict, const std::string& str): verdict(verdict), message(str){}
};
