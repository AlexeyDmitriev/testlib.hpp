#pragma once


#include <cstdlib>
#include <stdexcept>
#include <string>
#include <cassert>
#include <map>
#include "exitCodes.hpp"

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
	#define ON_WINDOWS
#endif
	
class Verdict {
public:
	enum _verdict{
		OK,
		FAIL,
		WA,
		PE
	};
	/* implicit */ Verdict(_verdict verdict):result(verdict){}
	Verdict partially(int result){
		return Verdict(result + VERDICTS);
	}
	
	int exitCode(){
		switch(result){
			case OK:
				return OK_EXIT_CODE;
			case WA:
				return WA_EXIT_CODE;
			case FAIL:
				return FAIL_EXIT_CODE;
			case PE:
				return PE_EXIT_CODE;
			default:
				return PARTIALLY_EXIT_CODE + result - VERDICTS;
		}
	}
	std::string shortMessage(){
		switch(result){
			case OK:
				return "OK";
			case WA:
				return "Wrong answer";
			case FAIL:
				return "FAIL";
			case PE:
				return "Wrong output format";
			default:
				return "Partially correct";
		}
	}

	std::string outcome(){
		switch(result){
			case OK:
				return "accepted";
			case WA:
				return "wrong-answer";
			case FAIL:
				return "fail";
			case PE:
				return "presentation-error";
			default:
				return "partially-correct";
		}
	}
	bool operator == (Verdict right){
		return result == right.result;
	}
private:
	const static int VERDICTS = PE + 1;
	explicit Verdict(int result):result(result){}
	int result;
};

class VerdictException : std::exception {
public:
	Verdict verdict;
	std::string message;
	VerdictException(Verdict verdict, const std::string& str): verdict(verdict), message(str){}
};
