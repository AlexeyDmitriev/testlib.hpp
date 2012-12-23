#pragma once
using namespace std;

typedef Alias<string, LineReader> Line;

#ifdef ON_WINDOWS
	#define LINE_SEPARATOR "\r\n"
#else
	#define LINE_SEPARATOR "\n"
#endif