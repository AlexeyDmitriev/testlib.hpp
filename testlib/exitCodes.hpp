#pragma once

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
	
#ifndef PARTIALLY_EXIT_CODE
	#ifdef TESTSYS
		#define PARTIALLY_EXIT_CODE 50
	#else
		#define PARTIALLY_EXIT_CODE 0
	#endif
#endif
