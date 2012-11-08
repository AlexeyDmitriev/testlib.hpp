#pragma once
#include "core.hpp"

#ifndef OK_EXIT_CODE
	#define OK_EXIT_CODE 0
#endif

#ifndef WA_EXIT_CODE
	#ifdef EJUDGE
		#define WA_EXIT_CODE 5
	#else
		#define WA_EXIT_CODE 1
	#endif
#endif

#ifndef PE_EXIT_CODE
	#ifdef EJUDGE
		#define PE_EXIT_CODE 4
	#else
		#define PE_EXIT_CODE 2
	#endif
#endif

#ifndef FAIL_EXIT_CODE
	#ifdef EJUDGE
		#define FAIL_EXIT_CODE 6
	#else
		#define FAIL_EXIT_CODE 3
	#endif
#endif
	
inline int exitCode(Verdict verdict){
	switch(verdict){
		case Verdict::OK:
			return OK_EXIT_CODE;
		case Verdict::WA:
			return WA_EXIT_CODE;
		case Verdict::FAIL:
			return FAIL_EXIT_CODE;
		case Verdict::PE:
			return PE_EXIT_CODE;
		default:
			assert(false);
	}
}
