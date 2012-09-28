#pragma once


#include <cstdlib>
#include <stdexcept>
#include <string>

//TODO: proper OS choosing
#define ON_LINUX
//#define ON_WINDOWS


enum class Verdict{
	OK,
	FAIL,
	WA,
	PE
};


class ReadingException : std::exception {
	Verdict verdict;
	std::string str;
public:
	ReadingException(Verdict verdict, std::string str): verdict(verdict), str(str){}
};


inline void quit(Verdict verdict, std::string message){
	if(verdict == Verdict::OK)
		std::cout << "OK ";
	else
		std::cout << "FAIL ";
	std::cout << message;
	if(verdict == Verdict::OK)
		exit(0);
	else
		exit(1);
	//TODO: proper exit code management
}